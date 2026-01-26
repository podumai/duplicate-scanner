#ifndef DUPSCANNER_MEMORY_MANAGER_HPP
#define DUPSCANNER_MEMORY_MANAGER_HPP

#include <array>
#include <fstream>
#include <memory_resource>

namespace duplicate_scanner::core {

class [[nodiscard]] MemoryManager : public std::pmr::memory_resource {
  static constexpr std::size_t kInitialBufferSize{65'536};
  alignas(alignof(std::max_align_t)) inline static std::array<char, kInitialBufferSize> static_buffer{};
  static constexpr std::size_t kLargestGeneralPoolBlock{128};
  static constexpr std::size_t kLargestSmallPoolBlock{64};
  static constexpr std::size_t kMaxBlocksPerChunk{16};
  static constexpr std::pmr::pool_options kGeneralPoolOptions{
    .max_blocks_per_chunk = kMaxBlocksPerChunk, .largest_required_pool_block = kLargestGeneralPoolBlock
  };
  static constexpr std::pmr::pool_options kSmallPoolOptions{
    .max_blocks_per_chunk = kMaxBlocksPerChunk, .largest_required_pool_block = kLargestSmallPoolBlock
  };

  using Base = memory_resource;

  static MemoryManager memory_manager;

  MemoryManager() { std::pmr::set_default_resource(this); }

 public:
  MemoryManager(MemoryManager const&) = delete;
  MemoryManager(MemoryManager&&) = delete;
  ~MemoryManager() override = default;

  auto operator=(MemoryManager const&) -> MemoryManager& = delete;
  auto operator=(MemoryManager&&) -> MemoryManager& = delete;

  [[nodiscard]] static auto instance() -> MemoryManager&;

 protected:
  [[nodiscard]] auto do_allocate(std::size_t bytes, std::size_t alignment) -> void* override;
  auto do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) -> void override;
  [[nodiscard]] auto do_is_equal(Base const& resource) const noexcept -> bool override;

 private:
  std::pmr::monotonic_buffer_resource buffer_resource_{
    static_buffer.data(), static_buffer.size(), std::pmr::new_delete_resource()
  };
  std::pmr::unsynchronized_pool_resource general_pool_resource_{kGeneralPoolOptions, &buffer_resource_};
  std::pmr::unsynchronized_pool_resource small_object_resource_{kSmallPoolOptions, &buffer_resource_};
};

}  // namespace duplicate_scanner::core

#endif  // DUPSCANNER_MEMORY_MANAGER_HPP
