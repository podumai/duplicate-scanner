#ifndef DUPSCANNER_MD5_HASHER_HPP
#define DUPSCANNER_MD5_HASHER_HPP

#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>

namespace duplicate_scanner::utility {
class [[nodiscard]] MD5Hasher : public details::AbstractHasher {
public:
  MD5Hasher() = default;
  MD5Hasher(MD5Hasher const&) = default;
  MD5Hasher(MD5Hasher&&) = default;
  ~MD5Hasher() override = default;

  auto operator=(MD5Hasher const&) -> MD5Hasher& = default;
  auto operator=(MD5Hasher&&) -> MD5Hasher& = default;

  [[nodiscard]] auto operator()(std::span<char const> bytes) const -> std::size_t override;
};
}

#endif  // DUPSCANNER_MD5_HASHER_HPP
