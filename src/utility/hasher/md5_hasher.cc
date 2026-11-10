#include <duplicate_scanner/utility/hasher/md5_hasher.hpp>
#include <boost/hash2/md5.hpp>
#include <boost/hash2/hash_append.hpp>

namespace duplicate_scanner::utility {

auto MD5Hasher::operator()(std::span<char const> const bytes) const -> std::size_t {
  auto hasher = boost::hash2::md5_128{};
  boost::hash2::hash_append(hasher, {}, bytes);
  return boost::hash2::get_integral_result<std::size_t>(hasher);
}

}
