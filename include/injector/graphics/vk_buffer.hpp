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
		VkBuffer(
			VmaAllocator allocator,
			size_t size,
			BufferType type,
			BufferUsage usage,
			const void* data = nullptr);
		virtual ~VkBuffer();

		VmaAllocator getAllocator() const noexcept;
		vk::Buffer getBuffer() const noexcept;
		VmaAllocation getAllocation() const noexcept;

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static vk::BufferUsageFlagBits getVkType(BufferType type);
		static BufferType getType(vk::BufferUsageFlagBits type);

		static VmaMemoryUsage getVkUsage(BufferUsage usage);
		static BufferUsage getUsage(VmaMemoryUsage usage);
	};

	using VkBufferHandle = std::shared_ptr<VkBuffer>;
}
