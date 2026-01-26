#include <duplicate_scanner/utility/file/file.hpp>

namespace duplicate_scanner::utility {

File::File(std::filesystem::path const& path, std::ios::openmode const mode) : Base{path, mode}, path_{path} { }

File::File(File&& other) : Base{std::move(other)}, path_{std::move(other.path_)} { }

auto File::open(char const* filename, openmode mode) -> void {
  path_ = std::filesystem::path{filename};
  Base::open(filename, mode);
}

auto File::open(std::string const& filename, openmode mode) -> void {
  path_ = filename;
  Base::open(filename, mode);
}

auto File::open(std::filesystem::path const& filename, openmode mode) -> void {
  path_ = filename;
  Base::open(filename, mode);
}

auto File::swap(File& other) -> void {
  if (this == &other) {
    return;
  }
  Base::swap(other);
  path_.swap(other.path_);
}

auto swap(File& lhs, File& rhs) -> void { lhs.swap(rhs); }

}  // namespace duplicate_scanner::utility
