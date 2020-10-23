#pragma once
#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Graphics/ImageData.hpp"
#include "Injector/Graphics/Vulkan/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	class VkGpuImage : public GpuImage
	{
	 protected:
		VmaAllocator allocator;
		vk::Image image;
		VmaAllocation allocation;
	 public:
		// TODO: handle not supported formats on platforms
		// VkGetPhysicalDeviceImageFormatProperties
		// https://stackoverflow.com/questions/38396578/vulkan-vkcreateimage-with-3-components
		VkGpuImage(
			VmaAllocator allocator,
			vk::ImageUsageFlags usageFlags,
			GpuImageType type,
			GpuImageFormat format,
			const IntVector3& size);
		~VkGpuImage() override;

		VmaAllocator getAllocator() const noexcept;
		vk::Image getImage() const noexcept;
		VmaAllocation getAllocation() const noexcept;
	};
}
