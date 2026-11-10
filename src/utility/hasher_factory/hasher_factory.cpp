#include <duplicate_scanner/utility/hasher/hasher.hpp>
#include <duplicate_scanner/utility/hasher_factory/hasher_factory.hpp>

namespace duplicate_scanner::utility {

std::pmr::unordered_map<std::string_view, HasherFactory::HasherPtrCreator> const HasherFactory::kHashers{
  {"md5", &std::make_unique<MD5Hasher>},
  {"sha3", &std::make_unique<SHA3Hasher>},
  {"blake2b", &std::make_unique<Blake2BHasher>},
};

auto HasherFactory::operator()(std::string_view const hasher_name) const -> HasherPtr {
  if (kHashers.contains(hasher_name)) [[likely]] {
    return kHashers.at(hasher_name)();
  }
  return nullptr;
}

}  // namespace duplicate_scanner::utility
