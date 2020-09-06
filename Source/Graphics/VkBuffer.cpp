#define VMA_IMPLEMENTATION
#include "Injector/Graphics/VkBuffer.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector::Graphics
{
	VkBuffer::VkBuffer(
		VmaAllocator _allocator,
		size_t _size,
		vk::BufferUsageFlags type,
		VmaMemoryUsage usage) :
		allocator(_allocator),
		size(_size),
		mapped(false),
		mapAccess(),
		mapSize(),
		mapOffset()
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = static_cast<VkBufferUsageFlags>(type);

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
		allocationCreateInfo.usage = usage;
		// TODO: VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED on mobiles

		VkBuffer_T* bufferHandle;
		allocation = nullptr;

		VmaAllocationInfo allocationInfo;

		auto result = vmaCreateBuffer(
			_allocator,
			&bufferCreateInfo,
			&allocationCreateInfo,
			&bufferHandle,
			&allocation,
			&allocationInfo);

		if(result != VK_SUCCESS)
			throw GraphicsException("Failed to create Vulkan buffer");

		buffer = vk::Buffer(bufferHandle);

		mappable =
			usage == VMA_MEMORY_USAGE_CPU_ONLY ||
			usage == VMA_MEMORY_USAGE_CPU_TO_GPU ||
			usage == VMA_MEMORY_USAGE_GPU_TO_CPU;
	}
	VkBuffer::~VkBuffer()
	{
		vmaDestroyBuffer(allocator, static_cast<VkBuffer_T*>(buffer), allocation);
	}

	VmaAllocator VkBuffer::getAllocator() const noexcept
	{
		return allocator;
	}
	vk::Buffer VkBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	VmaAllocation VkBuffer::getAllocation() const noexcept
	{
		return allocation;
	}
	size_t VkBuffer::getSize() const noexcept
	{
		return size;
	}
	bool VkBuffer::isMappable() const noexcept
	{
		return mappable;
	}
	bool VkBuffer::isMapped() const noexcept
	{
		return mapped;
	}
	BufferAccess VkBuffer::getMapAccess() const noexcept
	{
		return mapAccess;
	}
	size_t VkBuffer::getMapSize() const noexcept
	{
		return mapSize;
	}
	size_t VkBuffer::getMapOffset() const noexcept
	{
		return mapOffset;
	}

	void VkBuffer::invalidate(size_t _size, size_t offset)
	{
		auto result = vmaInvalidateAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to invalidate Vulkan buffer");
	}
	void VkBuffer::flush(size_t _size, size_t offset)
	{
		auto result = vmaFlushAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to flush Vulkan buffer");
	}

	void* VkBuffer::map(BufferAccess access)
	{
		if (!mappable)
			throw GraphicsException("Failed to map Vulkan buffer, not mappable");
		if (mapped)
			throw GraphicsException("Failed to map Vulkan buffer, already mapped");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to map Vulkan buffer");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
			invalidate(size, 0);

		mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;

		return mappedData;
	}
	void* VkBuffer::map(BufferAccess access, size_t _size, size_t offset)
	{
		if (!mappable)
			throw GraphicsException("Failed to map Vulkan buffer, not mappable");
		if (mapped)
			throw GraphicsException("Failed to map Vulkan buffer, already mapped");
		if (_size + offset > size)
			throw GraphicsException("Failed to map Vulkan buffer, out of range");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to map Vulkan buffer");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
			invalidate(_size, offset);

		mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;

		return mappedData;
	}
	void VkBuffer::unmap()
	{
		if (!mapped)
			throw GraphicsException("Failed to unmap Vulkan buffer, not mapped");

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
			flush(mapSize, mapOffset);

		vmaUnmapMemory(allocator, allocation);
		mapped = false;
	}

	void VkBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
			throw GraphicsException("Failed to set Vulkan buffer data, not mappable");
		if (mapped)
			throw GraphicsException("Failed to set Vulkan buffer data, already mapped");
		if(_size > size)
			throw GraphicsException("Failed to set Vulkan buffer data, out of range");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to map Vulkan buffer");

		memcpy(mappedData, data, _size);

		flush(_size, 0);
		vmaUnmapMemory(allocator, allocation);
	}
	void VkBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
			throw GraphicsException("Failed to set Vulkan buffer data, not mappable");
		if (mapped)
			throw GraphicsException("Failed to set Vulkan buffer data, already mapped");
		if (_size + offset > size)
			throw GraphicsException("Failed to set Vulkan buffer data, out of range");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to map Vulkan buffer");

		auto castedData = static_cast<char*>(mappedData);
		memcpy(castedData + offset, data, _size);

		flush(_size, offset);
		vmaUnmapMemory(allocator, allocation);
	}
}
