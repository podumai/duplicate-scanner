#include <duplicate_scanner/core/memory_manager/memory_manager.hpp>

namespace duplicate_scanner::core {

MemoryManager MemoryManager::memory_manager{};

[[nodiscard]] auto MemoryManager::instance() -> MemoryManager& { return memory_manager; }

[[nodiscard]] auto MemoryManager::do_allocate(std::size_t const bytes, std::size_t const alignment) -> void* {
  if (bytes <= kLargestSmallPoolBlock) {
    return small_object_resource_.allocate(bytes, alignment);
  }
  return general_pool_resource_.allocate(bytes, alignment);
}

auto MemoryManager::do_deallocate(void* ptr, std::size_t const bytes, std::size_t const alignment) -> void {
  if (bytes <= kLargestSmallPoolBlock) {
    small_object_resource_.deallocate(ptr, bytes, alignment);
    return;
  }
  general_pool_resource_.deallocate(ptr, bytes, alignment);
}

[[nodiscard]] auto MemoryManager::do_is_equal([[maybe_unused]] Base const& resource) const noexcept -> bool {
  return dynamic_cast<MemoryManager const*>(&resource);
}

}  // namespace duplicate_scanner::core
