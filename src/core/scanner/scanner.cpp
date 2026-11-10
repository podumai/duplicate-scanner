#include <spdlog/spdlog.h>

#include <algorithm>
#include <boost/regex.hpp>
#include <boost/smart_ptr/make_local_shared.hpp>
#include <duplicate_scanner/core/scanner/scanner.hpp>
#include <ranges>

namespace duplicate_scanner::core {

Scanner::Scanner(utility::Configuration const& configuration)
  : scan_depth_{configuration.scan_depth_}
  , block_size_{configuration.block_size_}
  , scan_directories_{configuration.scan_directories_} {
  excluded_directories_ =
    std::pmr::unordered_set<std::filesystem::path>{std::from_range, configuration.excluded_directories_};
  file_filter_ = [file_size = configuration.file_size_,
                  filename_mask = boost::regex{configuration.filename_mask_, boost::regex_constants::icase}](
                   auto const& directory_entry
                 ) -> bool {
    return std::filesystem::file_size(directory_entry) > file_size &&
      #ifndef _MSC_VER
           boost::regex_match(directory_entry.path().filename().c_str(), filename_mask);
      #else
           boost::regex_match(directory_entry.path().filename().string(), filename_mask);
      #endif
  };
  if (auto hasher{utility::HasherFactory{}(configuration.hash_func_)}; hasher) {
    hasher_ = std::move(hasher);
  } else {
    throw std::invalid_argument{"Invalid hash function provided."};
  }
}

[[nodiscard]] auto Scanner::makeFileGroup(std::filesystem::path const& directory_path) const
  -> std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> {
  std::filesystem::recursive_directory_iterator directory_traverser{
    directory_path, std::filesystem::directory_options::skip_permission_denied
  };
  std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> file_groups{};

  for (auto const& directory_entry : directory_traverser) {
    if (directory_entry.is_directory() && (std::cmp_greater_equal(directory_traverser.depth(), scan_depth_) ||
                                           excluded_directories_.contains(directory_entry))) {
      directory_traverser.disable_recursion_pending();
      continue;
    }
    if (directory_entry.is_regular_file() && file_filter_(directory_entry)) {
      constexpr utility::File::openmode kFileOpenMode{utility::File::in | utility::File::binary};
      auto file{boost::make_local_shared<utility::File>(directory_entry.path(), kFileOpenMode)};
      if (file->is_open()) {
        file_groups[directory_entry.file_size()].push_back(std::move(file));
      }
    }
  }
  return file_groups;
}

auto Scanner::printFileGroup(std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> const& file_groups) -> void {
  std::remove_reference_t<decltype(file_groups)>::size_type const file_groups_size{file_groups.size()};
  if (file_groups_size > 1) {
    spdlog::info("File groups:");
     for (auto const& [group_index, files] : std::views::zip(std::views::iota(0U), file_groups)) {
      spdlog::info("Group: {}", group_index);
       for (auto&& [local_index, file] : std::views::zip(std::views::iota(0U), files.second)) {
        spdlog::info("\t[{}] {}", local_index, file->path().native());
      }
    }
  } else if (file_groups_size == 1) {
    spdlog::info("Files:");
    for (auto&& [index, file] : std::views::zip(std::views::iota(0U), file_groups.cbegin()->second)) {
      spdlog::info("\t[{}] {}", index, file->path().c_str());
    }
  }
}

auto Scanner::run() const -> void {
  std::pmr::vector<char> buffer(block_size_, '\0');

  for (auto const& directory : scan_directories_) {
    if (!(std::filesystem::exists(directory) && std::filesystem::is_directory(directory))) {
      spdlog::warn("{} is not a valid directory path. Skipping.", directory.c_str());
      continue;
    }

    for (auto&& [file_size, file_group] :
         makeFileGroup(directory) | std::views::filter([] [[nodiscard]] (auto const& file_group_data) -> bool {
           return file_group_data.second.size() > 1;
         })) {
      std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> result{};
      std::pmr::vector files{std::move(file_group)};
      for (std::uintmax_t read_bytes{}; read_bytes < file_size; read_bytes += block_size_) {
        std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> filtered_file_groups{};
        std::ranges::for_each(
          files, [&buffer, &filtered_file_groups, this, buffer_size = buffer.size()](auto& file) -> void {
            if (!file->read(buffer.data(), buffer_size).eof()) {
              return;
            }
            if (auto const processed_bytes{file->gcount()}; processed_bytes < buffer_size) {
              std::fill(buffer.begin() + processed_bytes, buffer.end(), '\0');
            }
            filtered_file_groups[(*hasher_)(buffer)].push_back(file);
          }
        );
        if (filtered_file_groups.empty()) {
          break;
        }
        files.clear();
        std::erase_if(filtered_file_groups, [] [[nodiscard]] (auto const& file_group_data) noexcept -> bool {
          return file_group_data.second.size() == 1;
        });
        std::ranges::for_each(filtered_file_groups, [&files](auto const& bucket) -> void {
          std::ranges::copy(bucket.second, std::back_inserter(files));
        });
        result = std::move(filtered_file_groups);
      }

      printFileGroup(result);
    }
  }
}

}  // namespace duplicate_scanner::core
