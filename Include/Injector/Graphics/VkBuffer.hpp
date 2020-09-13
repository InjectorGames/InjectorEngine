#pragma once
#include "Injector/Graphics/Buffer.hpp"
#include "Injector/Graphics/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	class VkBuffer : public Buffer
	{
	protected:
		VmaAllocator allocator;
		vk::Buffer buffer;
		VmaAllocation allocation;
	public:
		VkBuffer(
			BufferType type,
			size_t size,
			VmaAllocator allocator,
			vk::BufferUsageFlags usageFlags,
			VmaMemoryUsage usage);
		virtual ~VkBuffer();

		VmaAllocator getAllocator() const noexcept;
		vk::Buffer getBuffer() const noexcept;
		VmaAllocation getAllocation() const noexcept;

		void invalidate(size_t size, size_t offset);
		void flush(size_t size, size_t offset);

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static vk::BufferUsageFlagBits toVkType(BufferType type);
		static bool isVkMappable(VmaMemoryUsage usage);
	};
}
