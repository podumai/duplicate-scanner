#include <duplicate_scanner/utility/hasher/blake2b_hasher.hpp>
#include <boost/hash2/blake2.hpp>
#include <boost/hash2/hash_append.hpp>

namespace duplicate_scanner::utility {

auto Blake2BHasher::operator()(std::span<char const> const bytes) const -> std::size_t {
  auto hasher = boost::hash2::blake2b_512{};
  boost::hash2::hash_append(hasher, {}, bytes);
  return boost::hash2::get_integral_result<std::size_t>(hasher);
}

}
