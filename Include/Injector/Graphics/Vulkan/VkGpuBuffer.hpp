#pragma once
#include "Injector/Graphics/GpuBuffer.hpp"
#include "Injector/Graphics/Vulkan/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	class VkGpuBuffer : public GpuBuffer
	{
	 protected:
		VmaAllocator allocator;
		vk::Buffer buffer;
		VmaAllocation allocation;

		static bool isVkMappable(
			VmaMemoryUsage usage);
	 public:
		VkGpuBuffer(
			VmaAllocator allocator,
			vk::BufferUsageFlags usageFlags,
			VmaMemoryUsage usage,
			GpuBufferType type,
			size_t size);
		~VkGpuBuffer() override;

		VmaAllocator getAllocator() const noexcept;
		vk::Buffer getBuffer() const noexcept;
		VmaAllocation getAllocation() const noexcept;

		void invalidate(
			size_t size,
			size_t offset);
		void flush(
			size_t size,
			size_t offset);

		void* map(
			GpuBufferAccess access) override;
		void* map(
			GpuBufferAccess access,
			size_t size,
			size_t offset) override;
		void unmap() override;

		void setData(
			const void* data,
			size_t size) override;
		void setData(
			const void* data,
			size_t size,
			size_t offset) override;
	};
}
