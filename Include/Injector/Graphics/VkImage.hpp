#pragma once
#include "Injector/Graphics/Image.hpp"
#include "Injector/Graphics/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector::Graphics
{
	class VkImage
	{
	protected:
		VmaAllocator allocator;
		vk::Image image;
		VmaAllocation allocation;
	public:
		VkImage(VmaAllocator allocator);
		virtual ~VkImage();
	};
}
