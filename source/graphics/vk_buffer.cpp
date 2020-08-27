#define VMA_IMPLEMENTATION
#include <injector/graphics/vk_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkBuffer::VkBuffer(
		VmaAllocator _allocator,
		size_t size,
		BufferType type,
		BufferUsage usage,
		const void* data,
		vk::BufferUsageFlags flags) :
		Buffer(size, type, usage),
		allocator(_allocator)
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = static_cast<VkBufferUsageFlags>(getVkType(type) | flags);

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
		allocationCreateInfo.usage = getVkUsage(usage);
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
			throw std::runtime_error("Failed to create Vulkan buffer");

		buffer = vk::Buffer(bufferHandle);

		if (data)
		{
			Buffer::map(BufferAccess::WriteOnly);

			void* mappedData;

			auto result = vmaMapMemory(allocator, allocation, &mappedData);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to map Vulkan buffer");

			memcpy(mappedData, data, size);

			Buffer::unmap();

			result = vmaFlushAllocation(allocator, allocation, 0, size);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to flush Vulkan buffer");

			vmaUnmapMemory(allocator, allocation);
		}
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
		Buffer::unmap();

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

		Buffer::map(BufferAccess::WriteOnly, _size, 0);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		memcpy(mappedData, data, _size);

		Buffer::unmap();

		result = vmaFlushAllocation(allocator, allocation, 0, _size);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to flush Vulkan buffer");

		vmaUnmapMemory(allocator, allocation);
	}
	void VkBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (_size + offset > size)
			throw std::runtime_error("Out of Vulkan buffer range");

		Buffer::map(BufferAccess::WriteOnly, _size, offset);

		void* mappedData;

		auto result = vmaMapMemory(allocator, allocation, &mappedData);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to map Vulkan buffer");

		auto castedData = static_cast<uint8_t*>(mappedData);
		memcpy(castedData + offset, data, _size);

		Buffer::unmap();

		result = vmaFlushAllocation(allocator, allocation, offset, _size);
		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to flush Vulkan buffer");

		vmaUnmapMemory(allocator, allocation);
	}

	vk::BufferUsageFlagBits VkBuffer::getVkType(BufferType type)
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
		case BufferType::TransformFeedbackCounterBuffer:
			return vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer type");
		}
	}
	BufferType VkBuffer::getType(vk::BufferUsageFlagBits type)
	{
		switch (type)
		{
		case vk::BufferUsageFlagBits::eUniformTexelBuffer:
			return BufferType::UniformTexel;
		case vk::BufferUsageFlagBits::eStorageTexelBuffer:
			return BufferType::StorageTexel;
		case vk::BufferUsageFlagBits::eUniformBuffer:
			return BufferType::Uniform;
		case vk::BufferUsageFlagBits::eStorageBuffer:
			return BufferType::Storage;
		case vk::BufferUsageFlagBits::eIndexBuffer:
			return BufferType::Index;
		case vk::BufferUsageFlagBits::eVertexBuffer:
			return BufferType::Vertex;
		case vk::BufferUsageFlagBits::eIndirectBuffer:
			return BufferType::Indirect;
		case vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT:
			return BufferType::TransformFeedback;
		case vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT:
			return BufferType::TransformFeedbackCounterBuffer;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer type");
		}
	}

	VmaMemoryUsage VkBuffer::getVkUsage(BufferUsage usage)
	{
		switch (usage)
		{
		case BufferUsage::CpuOnly:
			return VMA_MEMORY_USAGE_CPU_ONLY;
		case BufferUsage::GpuOnly:
			return VMA_MEMORY_USAGE_GPU_ONLY;
		case BufferUsage::CpuToGpu:
			return VMA_MEMORY_USAGE_CPU_TO_GPU;
		case BufferUsage::GpuToCpu:
			return VMA_MEMORY_USAGE_GPU_TO_CPU;
		case BufferUsage::CpuCopy:
			return VMA_MEMORY_USAGE_CPU_COPY;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer usage");
		}
	}
	BufferUsage VkBuffer::getUsage(VmaMemoryUsage usage)
	{
		switch (usage)
		{
		case VMA_MEMORY_USAGE_CPU_ONLY:
			return BufferUsage::CpuOnly;
		case VMA_MEMORY_USAGE_GPU_ONLY:
			return BufferUsage::GpuOnly;
		case VMA_MEMORY_USAGE_CPU_TO_GPU:
			return BufferUsage::CpuToGpu;
		case VMA_MEMORY_USAGE_GPU_TO_CPU:
			return BufferUsage::GpuToCpu;
		case VMA_MEMORY_USAGE_CPU_COPY:
			return BufferUsage::CpuCopy;
		default:
			throw std::runtime_error("Unsupported Vulkan buffer usage");
		}
	}
}
