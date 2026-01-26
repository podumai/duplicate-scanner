#ifndef DUPSCANNER_FILE_HANDLE_HPP
#define DUPSCANNER_FILE_HANDLE_HPP

#include <filesystem>
#include <fstream>

namespace duplicate_scanner::utility {

class [[nodiscard]] File : public std::fstream {
  using Base = std::fstream;

 public:
  File() = default;

  explicit File(std::filesystem::path const& path, std::ios::openmode mode = std::ios::in | std::ios::out);

  File(File const& other) = delete;

  File(File&& other);

  auto operator=(File const& other) -> File& = delete;

  auto operator=(File&& other) -> File& = default;

  ~File() override = default;

  auto open(char const* filename, openmode mode = in | out) -> void;

  auto open(std::string const& filename, openmode mode = in | out) -> void;

  auto open(std::filesystem::path const& filename, openmode mode = in | out) -> void;

  [[nodiscard]] auto path() const noexcept -> std::filesystem::path const& { return path_; }

  auto swap(File& other) -> void;

 private:
  std::filesystem::path path_;
};

auto swap(File& lhs, File& rhs) -> void;

}  // namespace duplicate_scanner::utility

#endif  // DUPSCANNER_FILE_HANDLE_HPP
