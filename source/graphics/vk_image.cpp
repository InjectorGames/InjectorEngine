#include <injector/graphics/vk_image.hpp>

namespace INJECTOR_NAMESPACE
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
			throw std::runtime_error("Failed to create Vulkan buffer");

		image = vk::Image(imageHandle);
	}
	VkImage::~VkImage()
	{
		vmaDestroyImage(allocator, static_cast<VkImage_T*>(image), allocation);
	}
}