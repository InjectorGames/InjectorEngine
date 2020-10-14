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
		VkGpuImage(
			VmaAllocator allocator,
			vk::ImageUsageFlags usageFlags,
			GpuImageType type,
			const IntVector3& size,
			GpuImageFormat format);
		~VkGpuImage() override;

		VmaAllocator getAllocator() const noexcept;
		vk::Image getImage() const noexcept;
		VmaAllocation getAllocation() const noexcept;

		static vk::Format toVkFormat(GpuImageFormat format);
	};
}
