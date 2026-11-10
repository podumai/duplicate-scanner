#ifndef DUPSCANNER_SHA3_HASHER_HPP
#define DUPSCANNER_SHA3_HASHER_HPP

#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>

namespace duplicate_scanner::utility {

class [[nodiscard]] SHA3Hasher : public details::AbstractHasher {
public:
  SHA3Hasher() = default;
  SHA3Hasher(SHA3Hasher const&) = default;
  SHA3Hasher(SHA3Hasher&&) = default;
  ~SHA3Hasher() override = default;

  auto operator=(SHA3Hasher const&) -> SHA3Hasher& = default;
  auto operator=(SHA3Hasher&&) -> SHA3Hasher& = default;

  [[nodiscard]] auto operator()(std::span<char const> bytes) const -> std::size_t override;
};

}

#endif  // DUPSCANNER_SHA3_HASHER_HPP
