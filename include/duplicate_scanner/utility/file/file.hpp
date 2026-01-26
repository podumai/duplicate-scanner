#ifndef DUPSCANNER_FILE_HANDLE_HPP
#define DUPSCANNER_FILE_HANDLE_HPP

#include <filesystem>
#include <fstream>

namespace duplicate_runner::utility {

class [[nodiscard]] File : public std::fstream {
  using Base = std::fstream;

 public:
  explicit File(std::filesystem::path const& path, std::ios::openmode const mode = std::ios::in | std::ios::out)
    : Base{path, mode}, path_{path} { }

  File(File const& other) = delete;

  File(
    File&& other
  ) noexcept(std::is_nothrow_move_constructible_v<std::filesystem::path> && std::is_nothrow_move_constructible_v<Base>)
    : Base{std::move(other)}, path_{std::move(other.path_)} { }

  auto operator=(File const& other) -> File& = delete;

  auto operator=(File&& other) noexcept(
    std::is_nothrow_move_assignable_v<std::filesystem::path> && std::is_nothrow_move_assignable_v<Base>
  ) -> File& {
    if (this == &other) {
      return *this;
    }
    path_ = std::move(other.path_);
    Base::operator=(std::move(other));
    return *this;
  }

  ~File() override = default;

  [[nodiscard]] auto filepath() const noexcept -> std::filesystem::path const& { return path_; }

 private:
  std::filesystem::path path_;
};

}  // namespace duplicate_runner::utility

#endif  // DUPSCANNER_FILE_HANDLE_HPP
