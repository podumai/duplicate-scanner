#ifndef DUPSCANNER_ABSTRACT_HASHER_HPP
#define DUPSCANNER_ABSTRACT_HASHER_HPP

#include <cstdint>
#include <span>

namespace duplicate_scanner::details {

class AbstractHasher {
 public:
  AbstractHasher() noexcept = default;
  AbstractHasher(const AbstractHasher&) noexcept = default;
  AbstractHasher(AbstractHasher&&) noexcept = default;
  virtual ~AbstractHasher() = default;

  auto operator=(const AbstractHasher&) noexcept -> AbstractHasher& = default;
  auto operator=(AbstractHasher&&) noexcept -> AbstractHasher& = default;

  [[nodiscard]] virtual auto operator()(std::span<char const> bytes) const -> std::size_t = 0;
};

}  // namespace duplicate_scanner::details

#endif  // DUPSCANNER_ABSTRACT_HASHER_HPP
