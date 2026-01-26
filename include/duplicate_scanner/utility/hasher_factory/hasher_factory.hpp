#ifndef DUPSCANNER_HASHER_FACTORY_HPP
#define DUPSCANNER_HASHER_FACTORY_HPP

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>
#include <string_view>
#include <unordered_set>

namespace duplicate_scanner::utility {

class [[nodiscard]] HasherFactory {
 public:
  using HasherPtr = boost::local_shared_ptr<details::AbstractHasher>;

 private:
  static const std::unordered_set<std::string_view, HasherPtr> kHashers;

 public:
  HasherFactory() noexcept = default;
  HasherFactory(const HasherFactory&) noexcept = default;
  HasherFactory(HasherFactory&&) noexcept = default;
  ~HasherFactory() = default;

  auto operator=(const HasherFactory&) noexcept -> HasherFactory& = default;
  auto operator=(HasherFactory&&) noexcept -> HasherFactory& = default;

  [[nodiscard]] auto operator()(const std::string_view hasher_name) const -> HasherPtr;
};

}  // namespace duplicate_scanner::utility

#endif  // DUPSCANNER_HASHER_FACTORY_HPP
