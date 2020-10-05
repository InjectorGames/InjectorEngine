#define VMA_IMPLEMENTATION
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"

namespace Injector
{
	VkGpuBuffer::VkGpuBuffer(
		GpuBufferType type,
		size_t size,
		VmaAllocator _allocator,
		vk::BufferUsageFlags usageFlags,
		VmaMemoryUsage usage) :
		GpuBuffer(type, size, isVkMappable(usage)),
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

		VkBuffer bufferHandle;
		allocation = nullptr;

		auto result = vmaCreateBuffer(
			_allocator,
			&bufferCreateInfo,
			&allocationCreateInfo,
			&bufferHandle,
			&allocation,
			nullptr);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"VkGpuBuffer",
				"Failed to create buffer");
		}

		buffer = vk::Buffer(bufferHandle);
	}
	VkGpuBuffer::~VkGpuBuffer()
	{
		vmaDestroyBuffer(
			allocator,
			static_cast<VkBuffer_T*>(buffer),
			allocation);
	}

	VmaAllocator VkGpuBuffer::getAllocator() const noexcept
	{
		return allocator;
	}
	vk::Buffer VkGpuBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	VmaAllocation VkGpuBuffer::getAllocation() const noexcept
	{
		return allocation;
	}

	void VkGpuBuffer::invalidate(
		size_t _size,
		size_t offset)
	{
		auto result = vmaInvalidateAllocation(
			allocator,
			allocation,
			offset,
			_size);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"invalidate",
				"Failed to invalidate");
		}
	}
	void VkGpuBuffer::flush(
		size_t _size,
		size_t offset)
	{
		auto result = vmaFlushAllocation(
			allocator,
			allocation,
			offset,
			_size);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"flush",
				"Failed to flush");
		}
	}

	void* VkGpuBuffer::map(GpuBufferAccess access)
	{
		if (!mappable)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Already mapped");
		}

		void* mappedData;

		auto result = vmaMapMemory(
			allocator,
			allocation,
			&mappedData);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Failed to map");
		}

		if (access == GpuBufferAccess::ReadOnly ||
			access == GpuBufferAccess::ReadWrite)
		{
			invalidate(size, 0);
		}

		mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
		return mappedData;
	}
	void* VkGpuBuffer::map(GpuBufferAccess access, size_t _size, size_t offset)
	{
		if (!mappable)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Already mapped");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				"VkGpuBuffer",
				"map",
				static_cast<uint64_t>(_size + offset),
				static_cast<uint64_t>(size));
		}

		void* mappedData;

		auto result = vmaMapMemory(
			allocator,
			allocation,
			&mappedData);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Failed to map");
		}

		if (access == GpuBufferAccess::ReadOnly ||
			access == GpuBufferAccess::ReadWrite)
		{
			invalidate(_size, offset);
		}

		mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
		return mappedData;
	}
	void VkGpuBuffer::unmap()
	{
		if (!mapped)
		{
			throw Exception(
				"VkGpuBuffer",
				"map",
				"Not mapped");
		}

		if (mapAccess == GpuBufferAccess::WriteOnly ||
			mapAccess == GpuBufferAccess::ReadWrite)
		{
			flush(mapSize, mapOffset);
		}

		vmaUnmapMemory(allocator, allocation);
		mapped = false;
	}

	void VkGpuBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Already mapped");
		}
		if(!data)
		{
			throw NullException(
				"VkGpuBuffer",
				"setData",
				"data");
		}
		if (_size > size)
		{
			throw OutOfRangeException(
				"VkGpuBuffer",
				"setData",
				static_cast<uint64_t>(_size),
				static_cast<uint64_t>(size));
		}

		void* mappedData;

		auto result = vmaMapMemory(
			allocator,
			allocation,
			&mappedData);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Failed to map");
		}

		memcpy(mappedData, data, _size);

		flush(_size, 0);
		vmaUnmapMemory(allocator, allocation);
	}
	void VkGpuBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Already mapped");
		}
		if(!data)
		{
			throw NullException(
				"VkGpuBuffer",
				"setData",
				"data");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				"VkGpuBuffer",
				"setData",
				static_cast<uint64_t>(_size + offset),
				static_cast<uint64_t>(size));
		}

		void* mappedData;

		auto result = vmaMapMemory(
			allocator,
			allocation,
			&mappedData);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkGpuBuffer",
				"setData",
				"Failed to map");
		}

		auto castedData = static_cast<char*>(mappedData);
		memcpy(castedData + offset, data, _size);

		flush(_size, offset);
		vmaUnmapMemory(allocator, allocation);
	}

	vk::BufferUsageFlagBits VkGpuBuffer::toVkType(GpuBufferType type)
	{
		switch (type)
		{
		case GpuBufferType::UniformTexel:
			return vk::BufferUsageFlagBits::eUniformTexelBuffer;
		case GpuBufferType::StorageTexel:
			return vk::BufferUsageFlagBits::eStorageTexelBuffer;
		case GpuBufferType::Uniform:
			return vk::BufferUsageFlagBits::eUniformBuffer;
		case GpuBufferType::Storage:
			return vk::BufferUsageFlagBits::eStorageBuffer;
		case GpuBufferType::Index:
			return vk::BufferUsageFlagBits::eIndexBuffer;
		case GpuBufferType::Vertex:
			return vk::BufferUsageFlagBits::eVertexBuffer;
		case GpuBufferType::Indirect:
			return vk::BufferUsageFlagBits::eIndirectBuffer;
		case GpuBufferType::TransformFeedback:
			return vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT;
		case GpuBufferType::TransformFeedbackCounter:
			return vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT;
		default:
			throw Exception(
				"VkGpuBuffer",
				"toVkType",
				"Unsupported type");
		}
	}
	bool VkGpuBuffer::isVkMappable(VmaMemoryUsage usage)
	{
		return
			usage == VMA_MEMORY_USAGE_CPU_ONLY ||
			usage == VMA_MEMORY_USAGE_CPU_TO_GPU ||
			usage == VMA_MEMORY_USAGE_GPU_TO_CPU;
	}
}
