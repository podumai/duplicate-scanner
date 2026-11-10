#ifndef DUPSCANNER_BLAKE2B_HASHER_HPP
#define DUPSCANNER_BLAKE2B_HASHER_HPP

#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>

namespace duplicate_scanner::utility {

class [[nodiscard]] Blake2BHasher : public details::AbstractHasher {
public:
  Blake2BHasher() = default;
  Blake2BHasher(Blake2BHasher const&) = default;
  Blake2BHasher(Blake2BHasher&&) = default;
  ~Blake2BHasher() override = default;

  auto operator=(Blake2BHasher const&) -> Blake2BHasher& = default;
  auto operator=(Blake2BHasher&&) -> Blake2BHasher& = default;

  [[nodiscard]] auto operator()(std::span<char const> bytes) const -> std::size_t override;
};

}

#endif  // DUPSCANNER_BLAKE2B_HASHER_HPP
