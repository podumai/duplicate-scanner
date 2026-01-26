#ifndef DUPSCANNER_HASHER_FACTORY_HPP
#define DUPSCANNER_HASHER_FACTORY_HPP

#include <duplicate_scanner/details/abstract_hasher/abstract_hasher.hpp>
#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>

namespace duplicate_scanner::utility {

class [[nodiscard]] HasherFactory {
 public:
  using HasherPtr = std::unique_ptr<details::AbstractHasher>;
  using HasherPtrCreator = std::function<HasherPtr()>;

 private:
  static std::pmr::unordered_map<std::string_view, HasherPtrCreator> const kHashers;

 public:
  HasherFactory() noexcept = default;
  HasherFactory(HasherFactory const&) noexcept = default;
  HasherFactory(HasherFactory&&) noexcept = default;
  ~HasherFactory() = default;

  auto operator=(HasherFactory const&) noexcept -> HasherFactory& = default;
  auto operator=(HasherFactory&&) noexcept -> HasherFactory& = default;

  [[nodiscard]] auto operator()(std::string_view hasher_name) const -> HasherPtr;
};

}  // namespace duplicate_scanner::utility

#endif  // DUPSCANNER_HASHER_FACTORY_HPP
