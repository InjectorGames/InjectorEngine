#include "Injector/Graphics/VkImage.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	VkImage::VkImage(VmaAllocator _allocator) :
		allocator(_allocator)
	{
		VkImageCreateInfo imageCreateInfo = {};
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		// TODO: make universal buffer usage type
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

		VkImage_T* imageHandle;
		allocation = nullptr;

		auto result = vmaCreateImage(_allocator, &imageCreateInfo, &allocationCreateInfo,
			&imageHandle, &allocation, nullptr);

		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to create Vulkan buffer");

		image = vk::Image(imageHandle);
	}
	VkImage::~VkImage()
	{
		vmaDestroyImage(allocator, static_cast<VkImage_T*>(image), allocation);
	}
}
