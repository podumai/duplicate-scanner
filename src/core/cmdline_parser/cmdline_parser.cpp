#include <duplicate_scanner/core/cmdline_parser/cmdline_parser.hpp>
#include <duplicate_scanner/utility/hasher_factory/hasher_factory.hpp>
#include <iostream>
#include <memory>
#include <ranges>
#include <utility>

namespace program_options = boost::program_options;

namespace duplicate_scanner::core {

auto CmdLineParser::descriptionInstance() -> program_options::options_description const& {
  static std::unique_ptr<program_options::options_description> description{};
  if (!description) {
    description = std::make_unique<program_options::options_description>("Duplicate Scanner options");
    description->add_options() //
        (kCmdArgHelp.data(), "produce help message")
        (kCmdArgScanDir.data(), program_options::value<std::vector<std::filesystem::path>>()->multitoken()->default_value({std::filesystem::current_path()}, "./"), "directories to scan")
        (kCmdArgExcludeDir.data(), program_options::value<std::vector<std::filesystem::path>>()->multitoken()->default_value(std::vector<std::filesystem::path>{},""), "directories to exclude from scanning")
        (kCmdArgFilenameMask.data(), program_options::value<std::pmr::string>()->default_value(".+"), "mask for filtering filenames (UNIX regex expression)")
        (kCmdArgScanDepth.data(), program_options::value<unsigned>()->default_value(kDefaultScanDepth), "directory scanning depth")
        (kCmdArgBlockSize.data(), program_options::value<unsigned>()->default_value(kDefaultBlockSize),"block size to use for file partition")
        (kCmdArgFileSize.data(), program_options::value<std::uintmax_t>()->default_value(kDefaultFileSize), "minimum file size required for scanning")
        (kCmdArgHashFunc.data(), program_options::value<std::pmr::string>()->default_value("sha3"), "hashing function to use for block comparison [md5, sha3, blake2]");
  }
  return *description;
}

auto CmdLineParser::parse(std::span<char const* const> args) -> void {
  boost::program_options::store(
    program_options::command_line_parser{static_cast<int>(args.size()), args.data()}  //
      .options(descriptionInstance())
      .run(),
    variables_map_
  );
  boost::program_options::notify(variables_map_);
}

auto CmdLineParser::normalizePaths(std::pmr::vector<std::filesystem::path>& paths) -> void {
  for (auto& path : paths | std::views::filter([](auto const& path) noexcept -> bool { return path.is_relative(); })) {
    path = std::filesystem::canonical(path);
  }
}

[[nodiscard]] auto CmdLineParser::createConfiguration() const -> utility::Configuration {
  utility::Configuration configuration{};
  configuration.scan_depth_ = variables_map_[kCmdArgScanDepth.data()].as<unsigned>();
  configuration.block_size_ = variables_map_[kCmdArgBlockSize.data()].as<unsigned>();
  configuration.scan_directories_ = std::pmr::vector<std::filesystem::path>{
    std::from_range, variables_map_[kCmdArgScanDir.data()].as<std::vector<std::filesystem::path>>()
  };
  normalizePaths(configuration.scan_directories_);
  configuration.excluded_directories_ = std::pmr::vector<std::filesystem::path>{
    std::from_range, variables_map_[kCmdArgExcludeDir.data()].as<std::vector<std::filesystem::path>>()
  };
  normalizePaths(configuration.excluded_directories_);
  configuration.hash_func_ = variables_map_[kCmdArgHashFunc.data()].as<std::pmr::string>();
  configuration.filename_mask_ = variables_map_[kCmdArgFilenameMask.data()].as<std::pmr::string>();
  return configuration;
}

auto CmdLineParser::helpDescriptionRequested() const -> bool { return variables_map_.contains(kCmdArgHelp.data()); }

auto CmdLineParser::printHelpDescription() -> void { descriptionInstance().print(std::cout); }

}  // namespace duplicate_scanner::core
