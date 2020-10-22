#include "Injector/Graphics/Vulkan/VkWindow.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/Vulkan/VkGpuMesh.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImage.hpp"
#include "Injector/Graphics/Vulkan/VkCameraSystem.hpp"
#include "Injector/Graphics/Vulkan/VkRenderSystem.hpp"
#include "Injector/Graphics/Vulkan/Pipeline/VkColorGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/Pipeline/VkDiffuseGpuPipeline.hpp"

#include <map>
#include <vector>
#include <iostream>

namespace Injector
{
#define VK_FRAME_LAG 2

	VkBool32 VKAPI_CALL VkWindow::debugMessengerCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageTypes,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
			std::cout << "Engine Vulkan [VERBOSE]: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
			std::cout << "Engine Vulkan [INFO]: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			std::cout << "Engine Vulkan [WARNING]: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			std::cout << "Engine Vulkan [ERROR]: " << pCallbackData->pMessage << "\n";

		return VK_FALSE;
	}

	GLFWwindow* VkWindow::createWindow(
		const std::string& title,
		const IntVector2& size)
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		return glfwCreateWindow(
			size.x,
			size.y,
			title.c_str(),
			nullptr,
			nullptr);
	}
	vk::Instance VkWindow::createInstance(
		const std::string& appName,
		uint32_t appVersion)
	{
		vk::Instance instance;

		auto instanceLayers = std::vector<const char*>();

#ifndef NDEBUG
		instanceLayers.push_back("VK_LAYER_KHRONOS_validation");

		auto instanceLayerProperties =
			vk::enumerateInstanceLayerProperties();

		if (instanceLayerProperties.size() == 0)
		{
			throw Exception(
				"VkWindow",
				"createInstance",
				"Failed to get instance layer properties");
		}

		for (auto layer : instanceLayers)
		{
			auto found = false;

			for (auto& properties : instanceLayerProperties)
			{
				if (strcmp(layer, properties.layerName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				throw Exception(
					"VkWindow",
					"createInstance",
					"Failed to get instance layer \"" +
					std::string(layer) + "\"");
			}
		}
#endif

		uint32_t extensionCount;

		auto glfwInstanceExtensions =
			glfwGetRequiredInstanceExtensions(&extensionCount);

		if (extensionCount == 0)
		{
			throw Exception(
				"VkWindow",
				"createInstance",
				"Failed to get instance extensions");
		}

		auto instanceExtensions =
			std::vector<const char*>(extensionCount);

		for (size_t i = 0; i < extensionCount; i++)
			instanceExtensions[i] = glfwInstanceExtensions[i];

#ifndef NDEBUG
		instanceExtensions.push_back(
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		auto instanceExtensionProperties =
			vk::enumerateInstanceExtensionProperties();

		for (auto extension : instanceExtensions)
		{
			auto found = false;

			for (auto& properties : instanceExtensionProperties)
			{
				if (strcmp(extension, properties.extensionName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				throw Exception(
					"VkWindow",
					"createInstance",
					"Failed to get instance extension \"" +
					std::string(extension) + "\"");
			}
		}

		auto applicationInfo = vk::ApplicationInfo(
			appName.c_str(),
			appVersion,
			"Injector Engine",
			VK_MAKE_VERSION(
				INJECTOR_VERSION_MAJOR,
				INJECTOR_VERSION_MINOR,
				INJECTOR_VERSION_PATCH),
			VK_API_VERSION_1_0);

		auto instanceCreateInfo = vk::InstanceCreateInfo({},
			&applicationInfo,
			static_cast<uint32_t>(instanceLayers.size()),
			instanceLayers.data(),
			static_cast<uint32_t>(instanceExtensions.size()),
			instanceExtensions.data());

#if !defined(NDEBUG)
		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT({},
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback));

		instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#endif
		auto result = vk::createInstance(
			&instanceCreateInfo,
			nullptr,
			&instance);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createInstance",
				"Failed to create instance");
		}

		return instance;
	}
	vk::DebugUtilsMessengerEXT VkWindow::createDebugMessenger(
		vk::Instance instance,
		const vk::DispatchLoaderDynamic& dispatchDynamic)
	{
#if !defined(NDEBUG)
		vk::DebugUtilsMessengerEXT debugMessenger;

		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT({},
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback));

		auto result = instance.createDebugUtilsMessengerEXT(
			&debugUtilsMessengerCreateInfo,
			nullptr,
			&debugMessenger,
			dispatchDynamic);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createDebugMessenger",
				"Failed to create debug messenger");
		}

		return debugMessenger;
#else
		return nullptr;
#endif
	}
	vk::PhysicalDevice VkWindow::getBestPhysicalDevice(
		vk::Instance instance)
	{
		auto physicalDevices = instance.enumeratePhysicalDevices();
		auto targetPhysicalDevices = std::multimap<int, vk::PhysicalDevice>();

		for (auto& device : physicalDevices)
		{
			auto score = 0;
			auto properties = device.getProperties();

			if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
				score += 1000;
			else if (properties.deviceType == vk::PhysicalDeviceType::eVirtualGpu)
				score += 750;
			else if (properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
				score += 500;
			else if (properties.deviceType == vk::PhysicalDeviceType::eCpu)
				score += 250;

			targetPhysicalDevices.emplace(score, device);
			// TODO: add other tests
		}

		if (targetPhysicalDevices.empty())
		{
			throw Exception(
				"VkWindow",
				"getBestPhysicalDevice",
				"Failed to find best physical devices");
		}

		return targetPhysicalDevices.rbegin()->second;
	}
	vk::SurfaceKHR VkWindow::createSurface(
		vk::Instance instance,
		GLFWwindow* window)
	{
		VkSurfaceKHR surfaceHandle;

		auto result = glfwCreateWindowSurface(
			instance,
			window,
			nullptr,
			&surfaceHandle);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkWindow",
				"createSurface",
				"Failed to create surface");
		}

		return vk::SurfaceKHR(surfaceHandle);
	}
	void VkWindow::getQueueFamilyIndices(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface,
		uint32_t& graphicsQueueFamilyIndex,
		uint32_t& presentQueueFamilyIndex)
	{
		auto queueFamilyProperties =
			physicalDevice.getQueueFamilyProperties();

		graphicsQueueFamilyIndex = UINT32_MAX;
		presentQueueFamilyIndex = UINT32_MAX;

		for (auto i = 0; i < queueFamilyProperties.size(); i++)
		{
			auto& properties = queueFamilyProperties[i];

			if (properties.queueFlags & vk::QueueFlagBits::eGraphics)
			{
				if (graphicsQueueFamilyIndex == UINT32_MAX)
					graphicsQueueFamilyIndex = i;
			}
			// TODO ONLY TEST: && graphicsQueueFamilyIndex != i
			if (physicalDevice.getSurfaceSupportKHR(i, surface))
			{
				if (presentQueueFamilyIndex == UINT32_MAX)
					presentQueueFamilyIndex = i;
			}

			if (graphicsQueueFamilyIndex != UINT32_MAX &&
				presentQueueFamilyIndex != UINT32_MAX)
				break;
		}

		if (graphicsQueueFamilyIndex == UINT32_MAX)
		{
			throw Exception(
				"VkWindow",
				"getQueueFamilyIndices",
				"Failed to find graphics queue family");
		}
		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			throw Exception(
				"VkWindow",
				"getQueueFamilyIndices",
				"Failed to find present queue family");
		}
	}
	vk::Device VkWindow::createDevice(
		vk::PhysicalDevice physicalDevice,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex)
	{
		vk::Device device;

		auto deviceExtensionProperties =
			physicalDevice.enumerateDeviceExtensionProperties();

		// TODO: create extension request mechanism
		auto deviceExtensions = std::vector<const char*>() = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

		for (auto extension : deviceExtensions)
		{
			auto found = false;

			for (auto& properties : deviceExtensionProperties)
			{
				if (strcmp(extension, properties.extensionName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				throw Exception(
					"VkWindow",
					"createDevice",
					"Failed to find device extension \"" +
					std::string(extension) + "\"");
			}
		}

		auto priority = 1.0f;

		auto deviceQueueCreateInfo = vk::DeviceQueueCreateInfo({},
			graphicsQueueFamilyIndex,
			1,
			&priority);

		auto deviceQueueCreateInfos = std::vector<vk::DeviceQueueCreateInfo>() = {
			deviceQueueCreateInfo,
		};

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			deviceQueueCreateInfo.queueFamilyIndex = presentQueueFamilyIndex;
			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}

		// TODO: use device features

		auto deviceCreateInfo = vk::DeviceCreateInfo({},
			static_cast<uint32_t>(deviceQueueCreateInfos.size()),
			deviceQueueCreateInfos.data(),
			0,
			nullptr,
			static_cast<uint32_t>(deviceExtensions.size()),
			deviceExtensions.data(),
			nullptr);

		auto result = physicalDevice.createDevice(
			&deviceCreateInfo,
			nullptr,
			&device);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createDevice",
				"Failed to create device");
		}

		return device;
	}
	VmaAllocator VkWindow::createMemoryAllocator(
		vk::Instance instance,
		vk::PhysicalDevice physicalDevice,
		vk::Device device)
	{
		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.flags = VMA_ALLOCATOR_CREATE_EXTERNALLY_SYNCHRONIZED_BIT;
		allocatorInfo.physicalDevice = static_cast<VkPhysicalDevice>(physicalDevice);
		allocatorInfo.device = static_cast<VkDevice>(device);
		allocatorInfo.instance = static_cast<VkInstance>(instance);

		VmaAllocator allocator;
		auto result = vmaCreateAllocator(&allocatorInfo, &allocator);

		if (result != VK_SUCCESS)
		{
			throw Exception(
				"VkWindow",
				"createMemoryAllocator",
				"Failed to create memory allocator");
		}

		return allocator;
	}
	vk::Queue VkWindow::getQueue(
		vk::Device device,
		uint32_t queueFamilyIndex,
		uint32_t queueIndex)
	{
		auto queue = device.getQueue(queueFamilyIndex, queueIndex);

		if (!queue)
		{
			throw Exception(
				"VkWindow",
				"getQueue",
				"Failed to get queue");
		}

		return queue;
	}
	vk::CommandPool VkWindow::createCommandPool(
		vk::Device device,
		const vk::CommandPoolCreateFlags& flags,
		uint32_t queueFamilyIndex)
	{
		vk::CommandPool commandPool;

		auto commandPoolCreateInfo = vk::CommandPoolCreateInfo(
			flags,
			queueFamilyIndex);
		auto result = device.createCommandPool(
			&commandPoolCreateInfo,
			nullptr,
			&commandPool);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createCommandPool",
				"Failed to create command pool");
		}

		return commandPool;
	}
	vk::Fence VkWindow::createFence(
		vk::Device device,
		const vk::FenceCreateFlags& flags)
	{
		vk::Fence fence;

		auto fenceCreateInfo = vk::FenceCreateInfo(flags);

		auto result = device.createFence(
			&fenceCreateInfo,
			nullptr,
			&fence);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createFence",
				"Failed to create fence");
		}

		return fence;
	}
	vk::Semaphore VkWindow::createSemaphore(
		vk::Device device,
		const vk::SemaphoreCreateFlags& flags)
	{
		vk::Semaphore semaphore;

		auto fenceCreateInfo = vk::SemaphoreCreateInfo(flags);

		auto result = device.createSemaphore(
			&fenceCreateInfo,
			nullptr,
			&semaphore);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"createSemaphore",
				"Failed to create semaphore");
		}

		return semaphore;
	}

	VkWindow::VkWindow(
		const std::string& title,
		const IntVector2& size) :
		Window(createWindow(title, size)),
		graphicsQueueFamilyIndex(UINT32_MAX),
		presentQueueFamilyIndex(UINT32_MAX)
	{
		if(size.x < 1 || size.y < 1)
		{
			throw Exception(
				"VkWindow",
				"VkWindow",
				"Incorrect size");
		}

		instance = createInstance(
			title,
			1);

		try
		{
			dispatchDynamic = vk::DispatchLoaderDynamic(
				static_cast<VkInstance>(instance),
				vkGetInstanceProcAddr);
			debugMessenger = createDebugMessenger(
				instance,
				dispatchDynamic);

			physicalDevice = getBestPhysicalDevice(
				instance);
			surface = createSurface(
				instance,
				window);

			getQueueFamilyIndices(
				physicalDevice,
				surface,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex);

			device = createDevice(
				physicalDevice,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex);
			memoryAllocator = createMemoryAllocator(
				instance,
				physicalDevice,
				device);

			graphicsQueue = getQueue(
				device,
				graphicsQueueFamilyIndex,
				0);
			presentQueue = getQueue(
				device,
				presentQueueFamilyIndex,
				0);

			if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
			{
				graphicsCommandPool = createCommandPool(
					device,
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
					graphicsQueueFamilyIndex);
				presentCommandPool = createCommandPool(
					device,
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
					presentQueueFamilyIndex);
			}
			else
			{
				graphicsCommandPool = presentCommandPool = createCommandPool(
					device,
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
					graphicsQueueFamilyIndex);
			}

			transferCommandPool = createCommandPool(
				device,
				vk::CommandPoolCreateFlagBits::eTransient,
				graphicsQueueFamilyIndex);

			fences = std::vector<vk::Fence>(VK_FRAME_LAG);
			imageAcquiredSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);
			drawCompleteSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);
			imageOwnershipSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);

			for (size_t i = 0; i < VK_FRAME_LAG; i++)
			{
				fences[i] = createFence(
					device,
					vk::FenceCreateFlagBits::eSignaled);
				imageAcquiredSemaphores[i] = createSemaphore(
					device,
					vk::SemaphoreCreateFlags());
				drawCompleteSemaphores[i] = createSemaphore(
					device,
					vk::SemaphoreCreateFlags());
				imageOwnershipSemaphores[i] = createSemaphore(
					device,
					vk::SemaphoreCreateFlags());
			}

			swapchain = VkGpuSwapchain(
				device,
				physicalDevice,
				surface,
				graphicsCommandPool,
				presentCommandPool,
				size);

			frameIndex = 0;
		}
		catch (const std::exception& exception)
		{
#ifndef NDEBUG
			instance.destroy(
				debugMessenger,
				nullptr,
				dispatchDynamic);
#else
			instance.destroy();
#endif
			throw exception;
		}
	}
	VkWindow::~VkWindow()
	{
		device.waitIdle();

		entities.clear();
		systems.clear();

		swapchain = VkGpuSwapchain();

		for (uint32_t i = 0; i < VK_FRAME_LAG; i++)
		{
			device.waitForFences(
				1,
				&fences[i],
				VK_TRUE,
				UINT64_MAX);

			device.destroyFence(fences[i]);
			device.destroySemaphore(imageAcquiredSemaphores[i]);
			device.destroySemaphore(drawCompleteSemaphores[i]);
			device.destroySemaphore(imageOwnershipSemaphores[i]);
		}

		device.destroyCommandPool(transferCommandPool);

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			device.destroyCommandPool(graphicsCommandPool);
			device.destroyCommandPool(presentCommandPool);
		}
		else
		{
			device.destroyCommandPool(graphicsCommandPool);
		}

		vmaDestroyAllocator(memoryAllocator);

		device.waitIdle();
		device.destroy();

		instance.destroySurfaceKHR(surface);

#ifndef NDEBUG
		instance.destroy(
			debugMessenger,
			nullptr,
			dispatchDynamic);
#else
		instance.destroy();
#endif
	}

	void VkWindow::onFramebufferResize(
		const IntVector2& size)
	{
		device.waitIdle();

		swapchain.resize(
			surface,
			graphicsCommandPool,
			presentCommandPool,
			size);

		while (true)
		{
		repeat:

			for (auto i = pipelines.begin(); i != pipelines.end(); i++)
			{
				auto& pipeline = *i;

				if (pipeline.use_count() <= 1)
				{
					pipelines.erase(i);
					goto repeat;
				}
			}

			break;
		}

		for (auto& pipeline : pipelines)
		{
			pipeline->recreate(
				memoryAllocator,
				swapchain.getRenderPass(),
				swapchain.getDatas().size(),
				swapchain.getExtent());
		}

		frameIndex = 0;
	}

	vk::CommandBuffer VkWindow::getGraphicsCommandBuffer(
		uint32_t imageIndex) const
	{
		auto& swapchainData = swapchain.getDatas();
		return swapchainData.at(imageIndex)->graphicsCommandBuffer;
	}

	uint32_t VkWindow::beginImage()
	{
		auto result = device.waitForFences(
			1,
			&fences[frameIndex],
			true,
			UINT64_MAX);

		if(result != vk::Result::eSuccess &&
			result != vk::Result::eTimeout)
		{
			throw Exception(
				"VkWindow",
				"beginImage",
				"Failed to wait for fence");
		}

		device.resetFences(
			{ fences[frameIndex] });

		uint32_t imageIndex;

		do
		{
			result = device.acquireNextImageKHR(
				swapchain.getSwapchain(),
				UINT64_MAX,
				imageAcquiredSemaphores[frameIndex],
				vk::Fence(),
				&imageIndex);

			if (result == vk::Result::eErrorOutOfDateKHR)
			{
				auto size = getFramebufferSize();
				onFramebufferResize(size);

				std::cout << "Engine Vulkan: Recreated outdated swapchain";
			}
			else if (result == vk::Result::eErrorSurfaceLostKHR)
			{
				instance.destroySurfaceKHR(
					surface);
				surface = createSurface(
					instance,
					window);

				auto size = getFramebufferSize();
				onFramebufferResize(size);

				std::cout << "Engine Vulkan: Recreated lost surface and swapchain";
			}
			else if (result != vk::Result::eSuccess &&
				result != vk::Result::eSuboptimalKHR)
			{
				throw Exception(
					"VkWindow",
					"beginImage",
					"Failed to acquire next image");
			}
		} while (result != vk::Result::eSuccess);

		vmaSetCurrentFrameIndex(
			memoryAllocator,
			imageIndex);

		return imageIndex;
	}
	void VkWindow::endImage(uint32_t imageIndex)
	{
		vk::PipelineStageFlags waitDestinationStageMask =
			vk::PipelineStageFlagBits::eColorAttachmentOutput;

		auto& swapchainDatas = swapchain.getDatas();
		auto swapchainData = swapchainDatas.at(imageIndex);

		auto submitInfo = vk::SubmitInfo(
			1,
			&imageAcquiredSemaphores[frameIndex],
			&waitDestinationStageMask,
			1,
			&swapchainData->graphicsCommandBuffer,
			1,
			&drawCompleteSemaphores[frameIndex]);

		auto result = graphicsQueue.submit(
			1,
			&submitInfo,
			fences[frameIndex]);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"endImage",
				"Failed to submit graphics queue");
		}

		auto swapchainHandle = swapchain.getSwapchain();

		auto presentInfo = vk::PresentInfoKHR(
			1,
			&drawCompleteSemaphores[frameIndex],
			1,
			&swapchainHandle,
			&imageIndex);

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			submitInfo.pWaitSemaphores =
				&drawCompleteSemaphores[frameIndex];
			submitInfo.pCommandBuffers =
				&swapchainData->presentCommandBuffer;
			submitInfo.pSignalSemaphores =
				&imageOwnershipSemaphores[frameIndex];

			result = presentQueue.submit(
				1,
				&submitInfo,
				vk::Fence());

			if (result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"endImage",
					"Failed to submit present queue");
			}

			presentInfo.pWaitSemaphores =
				&imageOwnershipSemaphores[frameIndex];
		}

		frameIndex += 1;
		frameIndex %= VK_FRAME_LAG;

		result = presentQueue.presentKHR(&presentInfo);

		if (result == vk::Result::eErrorOutOfDateKHR)
		{
			auto size = getFramebufferSize();
			onFramebufferResize(size);
		}
		else if (result == vk::Result::eErrorSurfaceLostKHR)
		{
			instance.destroySurfaceKHR(surface);
			surface = createSurface(instance, window);

			auto size = getFramebufferSize();
			onFramebufferResize(size);
		}
		else if (result != vk::Result::eSuccess &&
			result != vk::Result::eSuboptimalKHR)
		{
			throw Exception(
				"VkWindow",
				"endImage",
				"Failed to present next image");
		}
	}

	void VkWindow::beginRecord(uint32_t imageIndex)
	{
		auto& swapchainDatas = swapchain.getDatas();
		auto swapchainData = swapchainDatas.at(imageIndex);

		auto graphicsCommandBuffer =
			swapchainData->graphicsCommandBuffer;

		auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
			vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
			nullptr);
		auto result = graphicsCommandBuffer.begin(&commandBufferBeginInfo);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkWindow",
				"beginRecord",
				"Failed to begin command buffer");
		}

		auto clearValues = vk::ClearValue(vk::ClearColorValue(
			std::array<float, 4>{
				0.0f,
				0.0f,
				0.0f,
				0.0f }));
		auto renderPassBeginInfo = vk::RenderPassBeginInfo(
			swapchain.getRenderPass(),
			swapchainData->framebuffer,
			vk::Rect2D(
				{ 0, 0 },
				swapchain.getExtent()),
			1,
			&clearValues);
		graphicsCommandBuffer.beginRenderPass(
			&renderPassBeginInfo,
			vk::SubpassContents::eInline);
	}
	void VkWindow::endRecord(uint32_t imageIndex)
	{
		auto& swapchainDatas = swapchain.getDatas();
		auto swapchainData = swapchainDatas.at(imageIndex);

		auto graphicsCommandBuffer =
			swapchainData->graphicsCommandBuffer;

		graphicsCommandBuffer.endRenderPass();

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			auto imageMemoryBarrier = vk::ImageMemoryBarrier(
				vk::AccessFlags(),
				vk::AccessFlags(),
				vk::ImageLayout::ePresentSrcKHR,
				vk::ImageLayout::ePresentSrcKHR,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex,
				swapchainData->image,
				vk::ImageSubresourceRange(
					vk::ImageAspectFlagBits::eColor,
					0,
					1,
					0,
					1));
			graphicsCommandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::DependencyFlags(),
				0,
				nullptr,
				0,
				nullptr,
				1,
				&imageMemoryBarrier);
		}

		graphicsCommandBuffer.end();

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			auto presentCommandBuffer = swapchainData->presentCommandBuffer;
			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eSimultaneousUse,
				nullptr);
			auto result = presentCommandBuffer.begin(&commandBufferBeginInfo);

			if (result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"endRecord",
					"Failed to begin command buffer");
			}

			auto imageMemoryBarrier = vk::ImageMemoryBarrier(
				vk::AccessFlags(),
				vk::AccessFlags(),
				vk::ImageLayout::ePresentSrcKHR,
				vk::ImageLayout::ePresentSrcKHR,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex,
				swapchainData->image,
				vk::ImageSubresourceRange(
					vk::ImageAspectFlagBits::eColor,
					0,
					1,
					0,
					1));
			presentCommandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::DependencyFlags(),
				0,
				nullptr,
				0,
				nullptr,
				1,
				&imageMemoryBarrier);

			presentCommandBuffer.end();
		}
	}

	std::shared_ptr<CameraSystem> VkWindow::createCameraSystem()
	{
		auto system = std::make_shared<VkCameraSystem>(*this);
		systems.push_back(system);
		return system;
	}
	std::shared_ptr<RenderSystem> VkWindow::createRenderSystem()
	{
		auto system = std::make_shared<VkRenderSystem>(*this);
		systems.push_back(system);
		return system;
	}

	std::shared_ptr<GpuBuffer> VkWindow::createBuffer(
		size_t size,
		GpuBufferType type,
		bool mappable,
		const void* data)
	{
		std::shared_ptr<VkGpuBuffer> buffer;

		if (mappable)
		{
			buffer = std::make_shared<VkGpuBuffer>(
				memoryAllocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_TO_GPU,
				type,
				size);
			buffer->setData(
				data,
				size);
		}
		else
		{
			buffer = std::make_shared<VkGpuBuffer>(
				memoryAllocator,
				vk::BufferUsageFlagBits::eTransferDst,
				VMA_MEMORY_USAGE_GPU_ONLY,
				type,
				size);

			auto stagingBuffer = VkGpuBuffer(
				memoryAllocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_ONLY,
				GpuBufferType::TransferSource,
				size);
			stagingBuffer.setData(
				data,
				size);

			vk::CommandBuffer commandBuffer;

			auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo(
				transferCommandPool,
				vk::CommandBufferLevel::ePrimary,
				1);
			auto result = device.allocateCommandBuffers(
				&commandBufferAllocateInfo,
				&commandBuffer);

			if (result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"createBuffer",
					"Failed to allocate command buffer");
			}

			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
			commandBuffer.begin(commandBufferBeginInfo);

			auto bufferCopy = vk::BufferCopy(
				0,
				0,
				size);
			commandBuffer.copyBuffer(
				stagingBuffer.getBuffer(),
				buffer->getBuffer(),
				1,
				&bufferCopy);

			commandBuffer.end();

			auto submitInfo = vk::SubmitInfo(
				0,
				nullptr,
				nullptr,
				1,
				&commandBuffer);
			result = graphicsQueue.submit(
				1,
				&submitInfo,
				nullptr);

			if(result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"createBuffer",
					"Failed to submit graphics queue");
			}

			graphicsQueue.waitIdle();

			device.freeCommandBuffers(
				transferCommandPool,
				1,
				&commandBuffer);
		}

		return buffer;
	}
	std::shared_ptr<GpuMesh> VkWindow::createMesh(
		size_t indexCount,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer)
	{
		auto vkVertexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(vertexBuffer);
		auto vkIndexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(indexBuffer);

		return std::make_shared<VkGpuMesh>(
			indexCount,
			vkVertexBuffer,
			vkIndexBuffer);
	}
	std::shared_ptr<ShaderData> VkWindow::readShaderData(
		const std::string& filePath)
	{
		auto fileStream = FileStream(
			filePath + ".spv",
			std::ios::in | std::ios::binary);

		auto shaderData = std::make_shared<ShaderData>();
		shaderData->code = std::vector<uint8_t>(fileStream.getSize());

		fileStream.read(
			shaderData->code.data(),
			fileStream.getSize());

		return shaderData;
	}
	std::shared_ptr<GpuShader> VkWindow::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		return std::make_shared<VkGpuShader>(device, stage, data);
	}
	std::shared_ptr<GpuImage> VkWindow::createImage(
		GpuImageType type,
		const IntVector3& size,
		GpuImageFormat format,
		GpuImageFilter minFilter,
		GpuImageFilter magFilter,
		GpuImageWrap wrapU,
		GpuImageWrap wrapV,
		GpuImageWrap wrapW,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		/*void Demo::set_image_layout(vk::Image image, vk::ImageAspectFlags aspectMask, vk::ImageLayout oldLayout, vk::ImageLayout newLayout,
			vk::AccessFlags srcAccessMask, vk::PipelineStageFlags src_stages, vk::PipelineStageFlags dest_stages) {
			assert(cmd);

			auto DstAccessMask = [](vk::ImageLayout const &layout) {
			  vk::AccessFlags flags;

			  switch (layout) {
			  case vk::ImageLayout::eTransferDstOptimal:
				  // Make sure anything that was copying from this image has
				  // completed
				  flags = vk::AccessFlagBits::eTransferWrite;
				  break;
			  case vk::ImageLayout::eColorAttachmentOptimal:
				  flags = vk::AccessFlagBits::eColorAttachmentWrite;
				  break;
			  case vk::ImageLayout::eDepthStencilAttachmentOptimal:
				  flags = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
				  break;
			  case vk::ImageLayout::eShaderReadOnlyOptimal:
				  // Make sure any Copy or CPU writes to image are flushed
				  flags = vk::AccessFlagBits::eShaderRead | vk::AccessFlagBits::eInputAttachmentRead;
				  break;
			  case vk::ImageLayout::eTransferSrcOptimal:
				  flags = vk::AccessFlagBits::eTransferRead;
				  break;
			  case vk::ImageLayout::ePresentSrcKHR:
				  flags = vk::AccessFlagBits::eMemoryRead;
				  break;
			  default:
				  break;
			  }

			  return flags;
			};

			auto const barrier = vk::ImageMemoryBarrier()
				.setSrcAccessMask(srcAccessMask)
				.setDstAccessMask(DstAccessMask(newLayout))
				.setOldLayout(oldLayout)
				.setNewLayout(newLayout)
				.setSrcQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
				.setDstQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
				.setImage(image)
				.setSubresourceRange(vk::ImageSubresourceRange(aspectMask, 0, 1, 0, 1));

			cmd.pipelineBarrier(src_stages, dest_stages, vk::DependencyFlagBits(), 0, nullptr, 0, nullptr, 1, &barrier);
		}*/

		auto image = std::make_shared<VkGpuImage>(
			memoryAllocator,
			vk::ImageUsageFlagBits::eTransferDst |
			vk::ImageUsageFlagBits::eSampled,
			type,
			size,
			format);

		if(!data)
		{
			auto stagingBufferSize =
				data->size.x * data->size.y * data->componentCount;
			auto stagingBuffer = VkGpuBuffer(
				memoryAllocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_ONLY,
				GpuBufferType::TransferSource,
				stagingBufferSize);
			stagingBuffer.setData(
				data->pixels.data(),
				stagingBufferSize);

			vk::CommandBuffer commandBuffer;

			auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo(
				transferCommandPool,
				vk::CommandBufferLevel::ePrimary,
				1);
			auto result = device.allocateCommandBuffers(
				&commandBufferAllocateInfo,
				&commandBuffer);

			if (result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"createImage",
					"Failed to allocate command buffer");
			}

			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
			commandBuffer.begin(commandBufferBeginInfo);

			auto barrier = vk::ImageMemoryBarrier(
				vk::AccessFlags(),
				vk::AccessFlagBits::eTransferWrite,
				vk::ImageLayout::eUndefined,
				vk::ImageLayout::eTransferDstOptimal,
				VK_QUEUE_FAMILY_IGNORED,
				VK_QUEUE_FAMILY_IGNORED,
				image->getImage(),
				vk::ImageSubresourceRange(
					vk::ImageAspectFlagBits::eColor,
					0,
					1,
					0,
					1));

			commandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eTopOfPipe,
				vk::PipelineStageFlagBits::eTransfer,
				vk::DependencyFlagBits(),
				0,
				nullptr,
				0,
				nullptr,
				1,
				&barrier);

			auto bufferImageCopy = vk::BufferImageCopy(
				0,
				0,
				0,
				vk::ImageSubresourceLayers(
					vk::ImageAspectFlagBits::eColor,
					0,
					0,
					1),
				vk::Offset3D(
					0,
					0,
					0),
				vk::Extent3D(
					size.x,
					size.y,
					size.z));
			commandBuffer.copyBufferToImage(
				stagingBuffer.getBuffer(),
				image->getImage(),
				vk::ImageLayout::eTransferDstOptimal,
				1,
				&bufferImageCopy);

			barrier = vk::ImageMemoryBarrier(
				vk::AccessFlagBits::eTransferWrite,
				vk::AccessFlagBits::eShaderRead,
				vk::ImageLayout::eTransferDstOptimal,
				vk::ImageLayout::eShaderReadOnlyOptimal,
				VK_QUEUE_FAMILY_IGNORED,
				VK_QUEUE_FAMILY_IGNORED,
				image->getImage(),
				vk::ImageSubresourceRange(
					vk::ImageAspectFlagBits::eColor,
					0,
					1,
					0,
					1));

			commandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eTransfer,
				vk::PipelineStageFlagBits::eFragmentShader,
				vk::DependencyFlagBits(),
				0,
				nullptr,
				0,
				nullptr,
				1,
				&barrier);

			commandBuffer.end();

			auto submitInfo = vk::SubmitInfo(
				0,
				nullptr,
				nullptr,
				1,
				&commandBuffer);
			result = graphicsQueue.submit(
				1,
				&submitInfo,
				nullptr);

			if(result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkWindow",
					"createImage",
					"Failed to submit graphics queue");
			}

			graphicsQueue.waitIdle();

			device.freeCommandBuffers(
				transferCommandPool,
				1,
				&commandBuffer);
		}

		return nullptr;
	}
	std::shared_ptr<GpuFramebuffer> VkWindow::createFramebuffer(
		const std::shared_ptr<GpuImage>& colorImage,
		const std::shared_ptr<GpuImage>& depthImage,
		const std::shared_ptr<GpuImage>& stencilImage)
	{
		// TODO:
		return nullptr;
	}

	std::shared_ptr<GpuPipeline> VkWindow::createColorPipeline(
		PrimitiveTopology primitiveTopology,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const Vector4& color)
	{
		auto vkVertexShader = std::dynamic_pointer_cast<VkGpuShader>(vertexShader);
		auto vkFragmentShader = std::dynamic_pointer_cast<VkGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<VkColorGpuPipeline>(
			device,
			swapchain.getRenderPass(),
			swapchain.getExtent(),
			primitiveTopology,
			vkVertexShader,
			vkFragmentShader,
			color);

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				"VkWindow",
				"createColorPipeline",
				"Failed to emplace");
		}

		return pipeline;
	}
	std::shared_ptr<GpuPipeline> VkWindow::createColorColorPipeline(
		PrimitiveTopology primitiveTopology,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		return nullptr;
	}
	std::shared_ptr<GpuPipeline> VkWindow::createDiffusePipeline(
		PrimitiveTopology primitiveTopology,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		return nullptr;
	}
	std::shared_ptr<GpuPipeline> VkWindow::createImageDiffusePipeline(
		PrimitiveTopology primitiveTopology,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& image)
	{
		// TODO:
		return nullptr;
	}
	std::shared_ptr<GpuPipeline> VkWindow::createSkyPipeline(
		PrimitiveTopology primitiveTopology,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		return nullptr;
	}
}
