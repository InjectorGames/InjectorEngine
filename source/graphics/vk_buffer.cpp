#define VMA_IMPLEMENTATION
#include <injector/graphics/vk_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkBuffer::VkBuffer(VmaAllocator _allocator,
		size_t size,
		vk::BufferUsageFlagBits _usage,
		vk::BufferUsageFlags usageFlags) :
		Buffer(size),
		allocator(_allocator),
		usage(_usage)
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = static_cast<VkBufferUsageFlags>(_usage | usageFlags);

		VmaAllocationCreateInfo allocationCreateInfo = {};
		// TODO: make universal buffer usage type
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

		VkBuffer_T* bufferHandle;

		auto result = vmaCreateBuffer(allocator, &bufferCreateInfo, &allocationCreateInfo,
			&bufferHandle, &allocation, nullptr);

		if(result != VK_SUCCESS)
			throw std::runtime_error("Failed to create Vulkan buffer");

		buffer = vk::Buffer(bufferHandle);
	}
	VkBuffer::~VkBuffer()
	{
		vmaDestroyBuffer(allocator, static_cast<VkBuffer_T*>(buffer), allocation);
	}

	BufferUsage VkBuffer::getUsage() const
	{
		return toUsage(usage);
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
		switch (usage)
		{
		case BufferUsage::UniformTexel:
			return vk::BufferUsageFlagBits::eUniformTexelBuffer;
		case BufferUsage::StorageTexel:
			return vk::BufferUsageFlagBits::eStorageTexelBuffer;
		case BufferUsage::Uniform:
			return vk::BufferUsageFlagBits::eUniformBuffer;
		case BufferUsage::Storage:
			return vk::BufferUsageFlagBits::eStorageBuffer;
		case BufferUsage::Index:
			return vk::BufferUsageFlagBits::eIndexBuffer;
		case BufferUsage::Vertex:
			return vk::BufferUsageFlagBits::eVertexBuffer;
		case BufferUsage::Indirect:
			return vk::BufferUsageFlagBits::eIndirectBuffer;
		case BufferUsage::TransformFeedback:
			return vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT;
		case BufferUsage::TransformFeedbackCounterBuffer:
			return vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer usage");
		}
	}
	BufferUsage VkBuffer::toUsage(vk::BufferUsageFlagBits usage)
	{
		switch (usage)
		{
		case vk::BufferUsageFlagBits::eUniformTexelBuffer:
			return BufferUsage::UniformTexel;
		case vk::BufferUsageFlagBits::eStorageTexelBuffer:
			return BufferUsage::StorageTexel;
		case vk::BufferUsageFlagBits::eUniformBuffer:
			return BufferUsage::Uniform;
		case vk::BufferUsageFlagBits::eStorageBuffer:
			return BufferUsage::Storage;
		case vk::BufferUsageFlagBits::eIndexBuffer:
			return BufferUsage::Index;
		case vk::BufferUsageFlagBits::eVertexBuffer:
			return BufferUsage::Vertex;
		case vk::BufferUsageFlagBits::eIndirectBuffer:
			return BufferUsage::Indirect;
		case vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT:
			return BufferUsage::TransformFeedback;
		case vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT:
			return BufferUsage::TransformFeedbackCounterBuffer;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer usage");
		}
	}
}
