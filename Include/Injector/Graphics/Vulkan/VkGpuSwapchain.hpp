#pragma once
#include "Injector/Graphics/Vulkan/VkGpuImage.hpp"
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/VkSwapchainData.hpp"

#include <set>

namespace Injector
{
	class VkGpuSwapchain
	{
	 protected:
		vk::Device device;
		vk::PhysicalDevice physicalDevice;
		vk::Extent2D extent;
		vk::SwapchainKHR swapchain;
		std::shared_ptr<VkGpuImage> depthImage;
		vk::ImageView depthImageView;
		vk::RenderPass renderPass;
		std::vector<std::shared_ptr<VkSwapchainData>> datas;

		static vk::SurfaceFormatKHR getBestSurfaceFormat(
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface);
		static vk::PresentModeKHR getBestPresentMode(
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface);
		static uint32_t getBestImageCount(
			const vk::SurfaceCapabilitiesKHR& capabilities);
		static vk::Extent2D getBestExtent(
			const vk::SurfaceCapabilitiesKHR& capabilities,
			const IntVector2& size);
		static vk::SurfaceTransformFlagBitsKHR getBestTransform(
			const vk::SurfaceCapabilitiesKHR& capabilities);
		static vk::CompositeAlphaFlagBitsKHR getBestCompositeAlpha(
			const vk::SurfaceCapabilitiesKHR& capabilities);
		static vk::SwapchainKHR createSwapchain(
			vk::Device device,
			vk::SurfaceKHR surface,
			uint32_t imageCount,
			vk::SurfaceFormatKHR surfaceFormat,
			vk::Extent2D extent,
			vk::SurfaceTransformFlagBitsKHR transform,
			vk::CompositeAlphaFlagBitsKHR compositeAlpha,
			vk::PresentModeKHR presentMode,
			vk::SwapchainKHR oldSwapchain = nullptr);
		static vk::RenderPass createRenderPass(
			vk::Device device,
			vk::Format colorFormat,
			vk::Format depthFormat);
		static GpuImageFormat getBestDepthFormat(
			vk::PhysicalDevice physicalDevice);
		static vk::ImageView createDepthImageView(
			vk::Device device,
			vk::Image image,
			vk::Format format);
		static std::vector<std::shared_ptr<VkSwapchainData>> createDatas(
			vk::Device device,
			vk::SwapchainKHR swapchain,
			vk::RenderPass renderPass,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			vk::Format format,
			vk::ImageView depthImageView,
			const vk::Extent2D& extent);
	 public:
		VkGpuSwapchain() noexcept;
		VkGpuSwapchain(
			VmaAllocator allocator,
			vk::Device device,
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			const IntVector2& size);
		VkGpuSwapchain(VkGpuSwapchain&& swapchain) noexcept;
		VkGpuSwapchain(const VkGpuSwapchain& swapchain) = delete;
		virtual ~VkGpuSwapchain();

		vk::Device getDevice() const noexcept;
		vk::PhysicalDevice getPhysicalDevice() const noexcept;
		const vk::Extent2D& getExtent() const noexcept;
		vk::SwapchainKHR getSwapchain() const noexcept;
		vk::RenderPass getRenderPass() const noexcept;
		const std::vector<std::shared_ptr<VkSwapchainData>>& getDatas() const noexcept;

		void resize(
			VmaAllocator allocator,
			vk::SurfaceKHR surface,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			const IntVector2& size);

		VkGpuSwapchain& operator=(
			VkGpuSwapchain&& swapchain) noexcept;
	};
}
