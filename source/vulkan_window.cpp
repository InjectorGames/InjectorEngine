#include <injector_engine.hpp>

namespace Injector
{
	const std::string VulkanWindow::DefaultVulkanName =
		"Injector Engine - Editor (Vulkan)";
	const vk::Extent2D VulkanWindow::DefaultVulkanExtent = vk::Extent2D(static_cast<uint32_t>(Window::DefaultSize.x), static_cast<uint32_t>(Window::DefaultSize.y));
	const std::vector<const char*> VulkanWindow::DefaultDeviceLayers = Vulkan::DefaultInstanceLayers;
	const std::vector<const char*> VulkanWindow::DefaultDeviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	void VulkanWindow::SetupVulkanWindow()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	VulkanWindow::VulkanWindow(const std::vector<const char*>& deviceLayers, const std::vector<const char*>& deviceExtensions, std::string title, glm::ivec2 size, GLFWmonitor* monitor, GLFWwindow* share) : Window(SetupVulkanWindow, title, size, monitor, share)
	{
		if (!Vulkan::IsInitialized())
			throw std::runtime_error("Failed to create Vulkan window: Vulkan is not initialized.");

		auto vulkanIntance = Vulkan::GetInstance();
		VkSurfaceKHR surfaceInstance = VK_NULL_HANDLE;
		if (glfwCreateWindowSurface(vulkanIntance, instance, nullptr, &surfaceInstance) != VK_SUCCESS)
			throw std::runtime_error("Failed to create Vulkan window surface.");
		surface = vk::SurfaceKHR(surfaceInstance);

		auto physicalDevices = vulkanIntance.enumeratePhysicalDevices();
		physicalDevice = Vulkan::GetBestPhysicalDevice(physicalDevices);

		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();
		graphicsQueueFamilyIndex = UINT32_MAX;
		presentQueueFamilyIndex = UINT32_MAX;

		for (size_t i = 0; i < queueFamilyProperties.size(); i++)
		{
			if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				graphicsQueueFamilyIndex = (uint32_t)i;
				if (physicalDevice.getSurfaceSupportKHR((uint32_t)i, surface))
					presentQueueFamilyIndex = (uint32_t)i;
				break;
			}
		}

		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			for (size_t i = 0; i < queueFamilyProperties.size(); i++)
			{
				if (physicalDevice.getSurfaceSupportKHR((uint32_t)i, surface))
				{
					presentQueueFamilyIndex = (uint32_t)i;
					break;
				}
			}
		}

		if (graphicsQueueFamilyIndex == UINT32_MAX || presentQueueFamilyIndex == UINT32_MAX)
			throw std::runtime_error("Failed to create Vulkan window: Failed to find graphics or present queue family.");

		auto queuePriority = 1.0f;
		std::vector<vk::DeviceQueueCreateInfo> deviceQueueCreateInfos;

		if (graphicsQueueFamilyIndex == presentQueueFamilyIndex)
		{
			deviceQueueCreateInfos.push_back(vk::DeviceQueueCreateInfo({}, graphicsQueueFamilyIndex, 1, &queuePriority));
		}
		else
		{
			deviceQueueCreateInfos.push_back(vk::DeviceQueueCreateInfo({}, graphicsQueueFamilyIndex, 1, &queuePriority));
			deviceQueueCreateInfos.push_back(vk::DeviceQueueCreateInfo({}, presentQueueFamilyIndex, 1, &queuePriority));
		}

		vk::DeviceCreateInfo deviceCreateInfo({}, (uint32_t)deviceQueueCreateInfos.size(), deviceQueueCreateInfos.data(), (uint32_t)deviceLayers.size(), deviceLayers.data(), (uint32_t)deviceExtensions.size(), deviceExtensions.data());
		device = physicalDevice.createDevice(deviceCreateInfo);

		graphicsQueue = device.getQueue(graphicsQueueFamilyIndex, 0);
		presentQueue = device.getQueue(presentQueueFamilyIndex, 0);

		auto surafceFormats = physicalDevice.getSurfaceFormatsKHR(surface);
		auto surfaceFormat = Vulkan::GetBestSurfaceFormat(surafceFormats);

		auto presentModes = physicalDevice.getSurfacePresentModesKHR(surface);
		auto presentMode = Vulkan::GetBestPresentMode(presentModes);

		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
		auto surfaceImageCount = Vulkan::GetBestSurfaceImageCount(surfaceCapabilities);
		auto surfaceImageExtent = Vulkan::GetBestSurfaceImageExtent(surfaceCapabilities);

		auto imageSharingMode = vk::SharingMode::eExclusive;
		auto queueFamilyIndices = std::vector<uint32_t>();

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			imageSharingMode = vk::SharingMode::eConcurrent;
			queueFamilyIndices.push_back(graphicsQueueFamilyIndex);
			queueFamilyIndices.push_back(presentQueueFamilyIndex);
		}

		// imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT for post processing 

		vk::SwapchainCreateInfoKHR swapchainCreateInfo({}, surface, surfaceImageCount, surfaceFormat.format, surfaceFormat.colorSpace, surfaceImageExtent, 1, vk::ImageUsageFlagBits::eColorAttachment, imageSharingMode, (uint32_t)queueFamilyIndices.size(), queueFamilyIndices.data(), surfaceCapabilities.currentTransform, vk::CompositeAlphaFlagBitsKHR::eOpaque, presentMode, VK_TRUE);
		swapchain = device.createSwapchainKHR(swapchainCreateInfo);

		// DEV

		auto vertShaderModule = VulkanShader(device, "resources/shaders/dev.vert.spv", Shader::Type::Vertex);
		auto fragShaderModule = VulkanShader(device, "resources/shaders/dev.frag.spv", Shader::Type::Fragment);

		std::vector<vk::PipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos =
		{
			vertShaderModule.GetPipelineStageCreateInfo(vk::ShaderStageFlagBits::eVertex),
			fragShaderModule.GetPipelineStageCreateInfo(vk::ShaderStageFlagBits::eFragment),
		};

		vk::AttachmentDescription attachmentDescription({}, surfaceFormat.format, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);

		vk::AttachmentReference attachmentReference(0, vk::ImageLayout::eColorAttachmentOptimal);
		vk::SubpassDescription subpassDescription({}, vk::PipelineBindPoint::eGraphics, 0, VK_NULL_HANDLE, 1, &attachmentReference);

		vk::SubpassDependency subpassDependency(VK_SUBPASS_EXTERNAL, 0, vk::PipelineStageFlagBits::eColorAttachmentOutput, vk::PipelineStageFlagBits::eColorAttachmentOutput, {}, vk::AccessFlagBits::eColorAttachmentWrite, {});

		vk::RenderPassCreateInfo renderPassCreateInfo({}, 1, &attachmentDescription, 1, &subpassDescription, 1, &subpassDependency);
		renderPass = device.createRenderPass(renderPassCreateInfo);

		vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo({}, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);

		vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo({}, vk::PrimitiveTopology::eTriangleList, VK_FALSE);

		vk::Viewport viewport(0.0f, 0.0f, (float)surfaceImageExtent.width, (float)surfaceImageExtent.height, 0.0f, 1.0f);
		vk::Rect2D scissor(vk::Offset2D(0, 0), surfaceImageExtent);
		vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo({}, 1, &viewport, 1, &scissor);

		vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo({}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack, vk::FrontFace::eClockwise, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);

		vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo({}, vk::SampleCountFlagBits::e1, VK_FALSE, 1.0f, VK_NULL_HANDLE, VK_FALSE, VK_FALSE);

		vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(VK_FALSE, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd, vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

		vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo({}, VK_FALSE, vk::LogicOp::eCopy, 1, &pipelineColorBlendAttachmentState, { 0.0f, 0.0f, 0.0f, 0.0f });

		// vk::DynamicState

		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo({}, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);
		pipelineLayout = device.createPipelineLayout(pipelineLayoutCreateInfo);

		vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo({}, static_cast<uint32_t>(pipelineShaderStageCreateInfos.size()), pipelineShaderStageCreateInfos.data(), &pipelineVertexInputStateCreateInfo, &pipelineInputAssemblyStateCreateInfo, VK_NULL_HANDLE, &pipelineViewportStateCreateInfo, &pipelineRasterizationStateCreateInfo, &pipelineMultisampleStateCreateInfo, VK_NULL_HANDLE, &pipelineColorBlendStateCreateInfo, VK_NULL_HANDLE, pipelineLayout, renderPass, 0, {}, -1);
		pipeline = device.createGraphicsPipeline({}, graphicsPipelineCreateInfo);

		vk::CommandPoolCreateInfo commandPoolCreateInfo({}, graphicsQueueFamilyIndex);
		commandPool = device.createCommandPool(commandPoolCreateInfo);

		auto images = device.getSwapchainImagesKHR(swapchain);
		imageViews.resize(images.size());
		framebuffers.resize(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{
			vk::ImageViewCreateInfo imageViewCreateInfo({}, images[i], vk::ImageViewType::e2D, surfaceFormat.format, vk::ComponentMapping(vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity), vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
			auto imageView = device.createImageView(imageViewCreateInfo);
			imageViews[i] = imageView;

			vk::FramebufferCreateInfo framebufferCreateInfo({}, renderPass, 1, &imageView, surfaceImageExtent.width, surfaceImageExtent.height, 1);
			auto framebuffer = device.createFramebuffer(framebufferCreateInfo);
			framebuffers[i] = framebuffer;
		}

		vk::CommandBufferAllocateInfo commandBufferAllocateInfo(commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t)surfaceImageCount);
		commandBuffers = device.allocateCommandBuffers(commandBufferAllocateInfo);

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			const auto& commandBuffer = commandBuffers[i];

			vk::CommandBufferBeginInfo commandBufferBeginInfo({}, VK_NULL_HANDLE);
			commandBuffer.begin(commandBufferBeginInfo);

			vk::ClearValue clearColor(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}));
			vk::RenderPassBeginInfo renderPassBeginInfo(renderPass, framebuffers[i], vk::Rect2D(vk::Offset2D(0, 0), surfaceImageExtent), 1, &clearColor);
			commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
			commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
			commandBuffer.draw(3, 1, 0, 0);
			commandBuffer.endRenderPass();

			commandBuffer.end();
		}

		frameCount = surfaceImageCount - 1;
		currentFrame = 0;
		imageAvailableSemaphores.resize(frameCount);
		renderFinishedSemaphores.resize(frameCount);
		inFlightFences.resize(frameCount);
		imagesInFlight.resize(surfaceImageCount);

		vk::SemaphoreCreateInfo semaphoreCreateInfo({});
		vk::FenceCreateInfo fenceCreateInfo(vk::FenceCreateFlagBits::eSignaled);

		for (size_t i = 0; i < frameCount; i++)
		{
			imageAvailableSemaphores[i] = device.createSemaphore(semaphoreCreateInfo);
			renderFinishedSemaphores[i] = device.createSemaphore(semaphoreCreateInfo);
			inFlightFences[i] = device.createFence(fenceCreateInfo);
		}
	}
	VulkanWindow::~VulkanWindow()
	{
		device.waitIdle();

		for (size_t i = 0; i < frameCount; i++)
		{
			device.destroySemaphore(renderFinishedSemaphores[i]);
			device.destroySemaphore(imageAvailableSemaphores[i]);
			device.destroyFence(inFlightFences[i]);
		}

		for (const auto& framebuffer : framebuffers)
			device.destroyFramebuffer(framebuffer);
		for (const auto& imageView : imageViews)
			device.destroyImageView(imageView);

		device.destroyCommandPool(commandPool);
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);
		device.destroySwapchainKHR(swapchain);

		auto vulkanInstance = Vulkan::GetInstance();
		vulkanInstance.destroySurfaceKHR(surface);

		device.destroy();
	}

	void VulkanWindow::OnDraw()
	{
		device.waitForFences(1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

		auto imageResult = device.acquireNextImageKHR(swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], {});

		if (imagesInFlight[imageResult.value])
			device.waitForFences(1, &imagesInFlight[imageResult.value], VK_TRUE, UINT64_MAX);

		imagesInFlight[imageResult.value] = inFlightFences[currentFrame];
		device.resetFences(1, &inFlightFences[currentFrame]);

		vk::PipelineStageFlags pipelineStageFlags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		vk::SubmitInfo submitInfo(1, &imageAvailableSemaphores[currentFrame], &pipelineStageFlags, 1, &commandBuffers[imageResult.value], 1, &renderFinishedSemaphores[currentFrame]);
		graphicsQueue.submit(1, &submitInfo, inFlightFences[currentFrame]);

		vk::PresentInfoKHR presentInfoKHR(1, &renderFinishedSemaphores[currentFrame], 1, &swapchain, &imageResult.value, VK_NULL_HANDLE);
		presentQueue.presentKHR(presentInfoKHR);
		presentQueue.waitIdle();

		currentFrame = (currentFrame + 1) % frameCount;
	}
}
