#pragma once
#include <injector/graphics/image.hpp>
#include <injector/graphics/vma_defines.hpp>

#include <vulkan/vulkan.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkImage : public Image
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
