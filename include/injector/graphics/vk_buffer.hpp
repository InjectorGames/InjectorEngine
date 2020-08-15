#pragma once
#include <injector/graphics/buffer.hpp>
#include <injector/graphics/vma_defines.hpp>

#include <vulkan/vulkan.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkBuffer : public Buffer
	{
	protected:
		VmaAllocator allocator;
		vk::Buffer buffer;
		VmaAllocation allocation;
	public:
		VkBuffer(VmaAllocator allocator,
			size_t size,
			vk::BufferUsageFlags usage);
		virtual ~VkBuffer();

		VmaAllocator getAllocator() const noexcept;
		vk::Buffer getBuffer() const noexcept;
		VmaAllocation getAllocation() const noexcept;

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static vk::BufferUsageFlagBits toVkUsage(BufferUsage usage);
		static BufferUsage toUsage(vk::BufferUsageFlagBits usage);
	};

	using VkBufferHandle = std::shared_ptr<VkBuffer>;
}
