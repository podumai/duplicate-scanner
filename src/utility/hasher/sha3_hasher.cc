#include <duplicate_scanner/utility/hasher/sha3_hasher.hpp>
#include <boost/hash2/sha3.hpp>
#include <boost/hash2/hash_append.hpp>

namespace duplicate_scanner::utility {

auto SHA3Hasher::operator()(std::span<char const> const bytes) const -> std::size_t {
  auto hasher = boost::hash2::sha3_256{};
  boost::hash2::hash_append(hasher, {}, bytes);
  return boost::hash2::get_integral_result<std::size_t>(hasher);
}

}
