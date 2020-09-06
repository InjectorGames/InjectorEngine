#pragma once
#include "Injector/Graphics/BufferAccess.hpp"
#include "Injector/Graphics/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector::Graphics
{
	class VkBuffer
	{
	protected:
		VmaAllocator allocator;
		vk::Buffer buffer;
		VmaAllocation allocation;
		size_t size;
		bool mappable;
		bool mapped;
		BufferAccess mapAccess;
		size_t mapSize;
		size_t mapOffset;
	public:
		VkBuffer(
			VmaAllocator allocator,
			size_t size,
			vk::BufferUsageFlags type,
			VmaMemoryUsage usage);
		virtual ~VkBuffer();

		VmaAllocator getAllocator() const noexcept;
		vk::Buffer getBuffer() const noexcept;
		VmaAllocation getAllocation() const noexcept;
		size_t getSize() const noexcept;
		bool isMappable() const noexcept;
		bool isMapped() const noexcept;
		BufferAccess getMapAccess() const noexcept;
		size_t getMapSize() const noexcept;
		size_t getMapOffset() const noexcept;

		void invalidate(size_t size, size_t offset);
		void flush(size_t size, size_t offset);

		void* map(BufferAccess access);
		void* map(BufferAccess access, size_t size, size_t offset);
		void unmap();

		void setData(const void* data, size_t size);
		void setData(const void* data, size_t size, size_t offset);
	};
}
