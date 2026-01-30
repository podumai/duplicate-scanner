#ifndef DUPSCANNER_SCANNER_HPP
#define DUPSCANNER_SCANNER_HPP

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <cstdint>
#include <duplicate_scanner/utility/config/config.hpp>
#include <duplicate_scanner/utility/file/file.hpp>
#include <duplicate_scanner/utility/hasher_factory/hasher_factory.hpp>
#include <filesystem>
#include <set>
#include <type_traits>
#include <unordered_set>
#include <vector>

namespace duplicate_scanner::core {

class [[nodiscard]] Scanner {
 public:
  explicit Scanner(utility::Configuration const& configuration);

  Scanner(Scanner const&) = delete;

  Scanner(Scanner&&) noexcept(
    std::conjunction_v<
      std::is_nothrow_move_constructible<std::function<bool(std::filesystem::directory_entry const&)>>,
      std::is_nothrow_move_constructible<std::pmr::vector<std::filesystem::path>>,
      std::is_nothrow_move_constructible<std::pmr::unordered_set<std::filesystem::path>>,
      std::is_nothrow_move_constructible<utility::HasherFactory::HasherPtr>>
  ) = default;

  ~Scanner() = default;

  auto operator=(Scanner const&) -> Scanner& = delete;

  auto operator=(Scanner&&) noexcept(
    std::conjunction_v<
      std::is_nothrow_move_assignable<std::function<bool(std::filesystem::directory_entry const&)>>,
      std::is_nothrow_move_assignable<std::pmr::vector<std::filesystem::path>>,
      std::is_nothrow_move_assignable<std::pmr::unordered_set<std::filesystem::path>>,
      std::is_nothrow_move_assignable<utility::HasherFactory::HasherPtr>>
  ) -> Scanner& = default;

 private:
  using HasherPtr = utility::HasherFactory::HasherPtr;
  using FilePtr = boost::local_shared_ptr<utility::File>;

  [[nodiscard]] auto makeFileGroup(std::filesystem::path const& directory_path) const
    -> std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>>;

  static auto printFileGroup(std::pmr::map<std::uintmax_t, std::pmr::vector<FilePtr>> const& file_groups) -> void;

 public:
  auto run() const -> void;

 private:
  unsigned scan_depth_{};
  unsigned block_size_{};
  std::pmr::vector<std::filesystem::path> scan_directories_;
  HasherPtr hasher_;
  std::pmr::unordered_set<std::filesystem::path> excluded_directories_;
  std::function<bool(std::filesystem::directory_entry const&)> file_filter_;
};

}  // namespace duplicate_scanner::core

#endif  // DUPSCANNER_SCANNER_HPP
