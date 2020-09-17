#include "Injector/Graphics/VkTexture.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
    /*VkTexture::VkTexture(
        TextureType type,
        IntVector3 size,
        VmaAllocator _allocator,
        VkFormat format,
        VkImageUsageFlags flags) :
        Texture(type, size),
		allocator(_allocator)
	{
		VkImageCreateInfo imageCreateInfo = {};
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

        if(type == TextureType::T1D)
            imageCreateInfo.imageType = VK_IMAGE_TYPE_1D;
        else if(type == TextureType::T2D)
            imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
        else if(type == TextureType::T3D)
            imageCreateInfo.imageType = VK_IMAGE_TYPE_3D;
        else
            throw GraphicsException("Unknown Vulkan texture type");

        imageCreateInfo.format = format;
        imageCreateInfo.extent = 
        {
            static_cast<uint32_t>(size.x),
            static_cast<uint32_t>(size.y),
            static_cast<uint32_t>(size.z),
        };
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageCreateInfo.flags = flags;
        imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT;
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

		VkImage_T* imageHandle;
		allocation = nullptr;

		auto result = vmaCreateImage(
            _allocator,
            &imageCreateInfo,
            &allocationCreateInfo,
			&imageHandle,
            &allocation,
            nullptr);

		if (result != VK_SUCCESS)
			throw GraphicsException("Failed to create Vulkan buffer");

		image = vk::Image(imageHandle);
	}
	VkTexture::~VkTexture()
	{
		vmaDestroyImage(allocator, static_cast<VkImage_T*>(image), allocation);
	}*/
}
