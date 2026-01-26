#ifndef DUPSCANNER_CONFIG_HPP
#define DUPSCANNER_CONFIG_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace duplicate_scanner::utility {

struct [[nodiscard]] Configuration final {
  unsigned scan_depth_;
  unsigned block_size_;
  std::uintmax_t file_size_;
  std::pmr::vector<std::filesystem::path> scan_directories_;
  std::pmr::vector<std::filesystem::path> excluded_directories_;
  std::pmr::string filename_mask_;
  std::pmr::string hash_func_;
};

}  // namespace duplicate_scanner::utility

#endif  // DUPSCANNER_CONFIG_HPP
