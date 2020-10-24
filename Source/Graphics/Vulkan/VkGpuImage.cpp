#include "Injector/Graphics/Vulkan/VkGpuImage.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImageType.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImageFormat.hpp"

namespace Injector
{
	VkGpuImage::VkGpuImage(
		VmaAllocator _allocator,
		vk::ImageUsageFlags usageFlags,
		GpuImageType type,
		GpuImageFormat format,
		const IntVector3& size) :
		GpuImage(
			type,
			format,
			size,
			false),
		allocator(_allocator)
	{
		if(size.x < 1 || size.y < 1 || size.z < 1)
		{
			throw Exception(
				std::string(typeid(VkGpuImage).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Size x/y/z is less than one");
		}
		if(!_allocator)
		{
			throw NullException(
				std::string(typeid(VkGpuImage).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"allocator");
		}

		VkImageCreateInfo imageCreateInfo = {};
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.flags = 0;
		imageCreateInfo.imageType = static_cast<VkImageType>(
			toVkGpuImageType(type));
		imageCreateInfo.format = static_cast<VkFormat>(
			toVkGpuImageFormat(format));
		imageCreateInfo.extent = {
			static_cast<uint32_t>(size.x),
			static_cast<uint32_t>(size.y),
			static_cast<uint32_t>(size.z),
		};
		imageCreateInfo.mipLevels = 1;
		imageCreateInfo.arrayLayers = 1;
		imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageCreateInfo.usage = static_cast<VkImageUsageFlags>(usageFlags);
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		// TODO: VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED on mobiles

		VkImage imageHandle;
		allocation = nullptr;

		auto result = vmaCreateImage(
			_allocator,
			&imageCreateInfo,
			&allocationCreateInfo,
			&imageHandle,
			&allocation,
			nullptr);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				std::string(typeid(*this).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to create image");
		}

		image = vk::Image(imageHandle);
	}
	VkGpuImage::~VkGpuImage()
	{
		vmaDestroyImage(
			allocator,
			static_cast<VkImage>(image),
			allocation);
	}

	VmaAllocator VkGpuImage::getAllocator() const noexcept
	{
		return allocator;
	}
	vk::Image VkGpuImage::getImage() const noexcept
	{
		return image;
	}
	VmaAllocation VkGpuImage::getAllocation() const noexcept
	{
		return allocation;
	}
}
