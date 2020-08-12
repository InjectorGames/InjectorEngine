#define VMA_IMPLEMENTATION
#include <injector/graphics/vk_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkBuffer::VkBuffer(VmaAllocator _allocator,
		size_t size,
		vk::BufferUsageFlagBits _usage) :
		Buffer(size),
		allocator(_allocator),
		usage(_usage)
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = static_cast<VkBufferUsageFlags>(_usage) |
			VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		// TODO: make universal buffer usage type
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

		VkBuffer_T* bufferHandle;

		auto result = vmaCreateBuffer(allocator, &bufferCreateInfo, &allocationCreateInfo,
			&bufferHandle, &allocation, nullptr);

		buffer = bufferHandle;
	}
	VkBuffer::~VkBuffer()
	{
		vmaDestroyBuffer(allocator, static_cast<VkBuffer_T*>(buffer), allocation);
	}

	BufferUsage VkBuffer::getUsage() const
	{
		return tousa
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

	void* VkBuffer::map(BufferAccess access)
	{
		Buffer::map(access);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
		{
			result = vmaInvalidateAllocation(allocator, allocation, 0, size);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to invalidate Vulkan buffer");
		}

		return mappedData;
	}
	void* VkBuffer::map(BufferAccess access, size_t size, size_t offset)
	{
		Buffer::map(access, size, offset);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
		{
			result = vmaInvalidateAllocation(allocator, allocation, offset, size);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to invalidate Vulkan buffer");
		}

		return mappedData;
	}
	void VkBuffer::unmap()
	{
		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
		{
			auto result = vmaFlushAllocation(allocator, allocation, mapOffset, mapSize);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to flush Vulkan buffer");
		}

		vmaUnmapMemory(allocator, allocation);
	}

	void VkBuffer::setData(const void* data, size_t _size)
	{
		if (_size > size)
			throw std::runtime_error("Out of Vulkan buffer range");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		memcpy(mappedData, data, _size);

		result = vmaFlushAllocation(allocator, allocation, 0, _size);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to flush Vulkan buffer");

		vmaUnmapMemory(allocator, allocation);
	}
	void VkBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (_size + offset > size)
			throw std::runtime_error("Out of Vulkan buffer range");

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		auto castedData = static_cast<uint8_t*>(mappedData);
		memcpy(castedData + offset, data, _size);

		result = vmaFlushAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to flush Vulkan buffer");

		vmaUnmapMemory(allocator, allocation);
	}

	vk::BufferUsageFlagBits VkBuffer::toVkUsage(BufferUsage usage)
	{

	}
	BufferUsage VkBuffer::toUsage(vk::BufferUsageFlagBits usage)
	{

	}
}
