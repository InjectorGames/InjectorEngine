#define VMA_IMPLEMENTATION
#include "Injector/Graphics/VkBuffer.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"

namespace Injector
{
	VkBuffer::VkBuffer(
		BufferType type,
		size_t size,
		VmaAllocator _allocator,
		vk::BufferUsageFlags usageFlags,
		VmaMemoryUsage usage) :
		Buffer(type, size, isVkMappable(usage)),
		allocator(_allocator)
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = static_cast<VkBufferUsageFlags>(toVkType(type) | usageFlags);

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
		allocationCreateInfo.usage = usage;
		// TODO: VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED on mobiles

		VkBuffer_T* bufferHandle;
		allocation = nullptr;

		auto result = vmaCreateBuffer(
			_allocator,
			&bufferCreateInfo,
			&allocationCreateInfo,
			&bufferHandle,
			&allocation,
			nullptr);

		if(result != VK_SUCCESS)
			throw Exception("VkBuffer", "VkBuffer", "Failed to create buffer");

		buffer = vk::Buffer(bufferHandle);
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

	void VkBuffer::invalidate(size_t _size, size_t offset)
	{
		auto result = vmaInvalidateAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "invalidate", "Failed to invalidate");
	}
	void VkBuffer::flush(size_t _size, size_t offset)
	{
		auto result = vmaFlushAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "fkush", "Failed to flush");
	}

	void* VkBuffer::map(BufferAccess access)
	{
		Buffer::map(access);
		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "map", "Failed to map");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
			invalidate(size, 0);

		return mappedData;
	}
	void* VkBuffer::map(BufferAccess access, size_t size, size_t offset)
	{
		Buffer::map(access);
		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "map", "Failed to map");

		if (access == BufferAccess::ReadOnly || access == BufferAccess::ReadWrite)
			invalidate(size, offset);

		return mappedData;
	}
	void VkBuffer::unmap()
	{
		Buffer::unmap();

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
			flush(mapSize, mapOffset);

		vmaUnmapMemory(allocator, allocation);
		mapped = false;
	}

	void VkBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
			throw Exception("VkBuffer", "setData", "Not mappable");
		if (mapped)
			throw Exception("VkBuffer", "setData", "Already mapped");
		if(_size > size)
			throw OutOfRangeException("VkBuffer", "setData", _size, size);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "setData", "Failed to map");

		memcpy(mappedData, data, _size);

		flush(_size, 0);
		vmaUnmapMemory(allocator, allocation);
	}
	void VkBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
			throw Exception("VkBuffer", "setData", "Not mappable");
		if (mapped)
			throw Exception("VkBuffer", "setData", "Already mapped");
		if (_size + offset > size)
			throw OutOfRangeException("VkBuffer", "setData", _size + offset, size);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw Exception("VkBuffer", "setData", "Failed to map");

		auto castedData = static_cast<char*>(mappedData);
		memcpy(castedData + offset, data, _size);

		flush(_size, offset);
		vmaUnmapMemory(allocator, allocation);
	}

	vk::BufferUsageFlagBits VkBuffer::toVkType(BufferType type)
	{
		switch (type)
		{
		case BufferType::UniformTexel:
			return vk::BufferUsageFlagBits::eUniformTexelBuffer;
		case BufferType::StorageTexel:
			return vk::BufferUsageFlagBits::eStorageTexelBuffer;
		case BufferType::Uniform:
			return vk::BufferUsageFlagBits::eUniformBuffer;
		case BufferType::Storage:
			return vk::BufferUsageFlagBits::eStorageBuffer;
		case BufferType::Index:
			return vk::BufferUsageFlagBits::eIndexBuffer;
		case BufferType::Vertex:
			return vk::BufferUsageFlagBits::eVertexBuffer;
		case BufferType::Indirect:
			return vk::BufferUsageFlagBits::eIndirectBuffer;
		case BufferType::TransformFeedback:
			return vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT;
		case BufferType::TransformFeedbackCounter:
			return vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT;
		default:
			throw Exception("VkBuffer", "toVkType", "Unsupported type");
		}
	}
	bool VkBuffer::isVkMappable(VmaMemoryUsage usage)
	{
		return 
			usage == VMA_MEMORY_USAGE_CPU_ONLY ||
			usage == VMA_MEMORY_USAGE_CPU_TO_GPU ||
			usage == VMA_MEMORY_USAGE_GPU_TO_CPU;
	}
}
