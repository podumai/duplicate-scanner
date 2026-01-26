#ifndef DUPSCANNER_HASHER_HPP
#define DUPSCANNER_HASHER_HPP

#include <boost/hash2/blake2.hpp>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/md5.hpp>
#include <boost/hash2/sha3.hpp>
#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>

namespace duplicate_scanner::utility {

template<typename HasherType>
class [[nodiscard]] Hasher final : public details::AbstractHasher {
 public:
  [[nodiscard]] auto operator()(const std::vector<char>& bytes) const -> std::size_t override {
    HasherType hasher{};
    boost::hash2::hash_append(hasher, {}, bytes);
    return boost::hash2::get_integral_result<std::size_t>(hasher);
  }
};

using MD5Hasher = Hasher<boost::hash2::md5_128>;
using SHA3Hasher = Hasher<boost::hash2::sha3_256>;
using Blake2bHasher = Hasher<boost::hash2::blake2b_512>;

}  // namespace duplicate_scanner::utility

#endif  // DUPSCANNER_HASHER_HPP
