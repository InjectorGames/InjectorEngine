#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/Vulkan/VkGpuMesh.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImage.hpp"
#include "Injector/Graphics/Vulkan/VkCameraEcsSystem.hpp"
#include "Injector/Graphics/Vulkan/VkRenderEcsSystem.hpp"
#include "Injector/Graphics/Vulkan/Pipeline/VkColorGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/Pipeline/VkDiffuseGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/Pipeline/VkImageDiffuseGpuPipeline.hpp"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_vulkan.h"

#include <map>
#include <vector>
#include <iostream>

namespace Injector
{
#define VK_FRAME_LAG 2

	VkBool32 VKAPI_CALL VkGpuWindow::debugMessengerCallback(
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

	GLFWwindow* VkGpuWindow::createWindow(
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
	vk::Instance VkGpuWindow::createInstance(
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
				THIS_FUNCTION_NAME,
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
					THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
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
					THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Failed to create instance");
		}

		return instance;
	}
	vk::DebugUtilsMessengerEXT VkGpuWindow::createDebugMessenger(
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
				THIS_FUNCTION_NAME,
				"Failed to create debug messenger");
		}

		return debugMessenger;
#else
		return nullptr;
#endif
	}
	vk::PhysicalDevice VkGpuWindow::getBestPhysicalDevice(
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
				THIS_FUNCTION_NAME,
				"Failed to find best physical devices");
		}

		return targetPhysicalDevices.rbegin()->second;
	}
	vk::SurfaceKHR VkGpuWindow::createSurface(
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
				THIS_FUNCTION_NAME,
				"Failed to create surface");
		}

		return vk::SurfaceKHR(surfaceHandle);
	}
	void VkGpuWindow::getQueueFamilyIndices(
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
			// ONLY TEST: && graphicsQueueFamilyIndex != i
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
				THIS_FUNCTION_NAME,
				"Failed to find graphics queue family");
		}
		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to find present queue family");
		}
	}
	vk::Device VkGpuWindow::createDevice(
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
					THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Failed to create device");
		}

		return device;
	}
	VmaAllocator VkGpuWindow::createMemoryAllocator(
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
				THIS_FUNCTION_NAME,
				"Failed to create memory allocator");
		}

		return allocator;
	}
	vk::Queue VkGpuWindow::getQueue(
		vk::Device device,
		uint32_t queueFamilyIndex,
		uint32_t queueIndex)
	{
		auto queue = device.getQueue(
			queueFamilyIndex,
			queueIndex);

		if (!queue)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get queue");
		}

		return queue;
	}
	vk::CommandPool VkGpuWindow::createCommandPool(
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
				THIS_FUNCTION_NAME,
				"Failed to create command pool");
		}

		return commandPool;
	}
	vk::Fence VkGpuWindow::createFence(
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
				THIS_FUNCTION_NAME,
				"Failed to create fence");
		}

		return fence;
	}
	vk::Semaphore VkGpuWindow::createSemaphore(
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
				THIS_FUNCTION_NAME,
				"Failed to create semaphore");
		}

		return semaphore;
	}

	VkGpuWindow::VkGpuWindow(
		const std::string& title,
		const IntVector2& size) :
		GpuWindow(createWindow(title, size)),
		graphicsQueueFamilyIndex(UINT32_MAX),
		presentQueueFamilyIndex(UINT32_MAX)
	{
		if (size.x < 1 || size.y < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Incorrect size");
		}

		instance = createInstance(
			title,
			1);
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
			memoryAllocator,
			device,
			physicalDevice,
			surface,
			graphicsCommandPool,
			presentCommandPool,
			size);

		// TODO:
		//ImGui_ImplGlfw_InitForVulkan(
		//	window,
		//	false);

		frameIndex = 0;
	}
	VkGpuWindow::~VkGpuWindow()
	{
		device.waitIdle();
		systems.clear();

		swapchain = VkGpuSwapchain();

		for (uint32_t i = 0; i < VK_FRAME_LAG; i++)
		{
			auto result = device.waitForFences(
				1,
				&fences[i],
				VK_TRUE,
				UINT64_MAX);

			if(result != vk::Result::eSuccess)
				std::cout << "Engine Vulkan: Failed to wait for fences\n";

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

	void VkGpuWindow::onFramebufferResize(
		const IntVector2& size)
	{
		if (size.x < 1 || size.y < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Size x/y is less than one");
		}

		device.waitIdle();

		swapchain.resize(
			memoryAllocator,
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
				static_cast<uint32_t>(
					swapchain.getDatas().size()),
				swapchain.getExtent());
		}

		frameIndex = 0;
	}

	vk::CommandBuffer VkGpuWindow::getGraphicsCommandBuffer(
		uint32_t imageIndex) const
	{
		auto& swapchainData = swapchain.getDatas();
		return swapchainData.at(imageIndex)->graphicsCommandBuffer;
	}

	uint32_t VkGpuWindow::beginImage()
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
				THIS_FUNCTION_NAME,
				"Failed to wait for fence");
		}

		device.resetFences({ fences[frameIndex] });

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
					THIS_FUNCTION_NAME,
					"Failed to acquire next image");
			}
		} while (result != vk::Result::eSuccess);

		vmaSetCurrentFrameIndex(
			memoryAllocator,
			imageIndex);

		return imageIndex;
	}
	void VkGpuWindow::endImage(uint32_t imageIndex)
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
				THIS_FUNCTION_NAME,
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
					THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Failed to present next image");
		}
	}

	void VkGpuWindow::beginRecord(uint32_t imageIndex)
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
				THIS_FUNCTION_NAME,
				"Failed to begin command buffer");
		}

		vk::ClearValue clearValues[2] =
		{
			vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{
				0.0f,
				0.0f,
				0.0f,
				1.0f, })),
			vk::ClearValue(vk::ClearDepthStencilValue(
				1.0f,
				0.0f)),
		};

		auto renderPassBeginInfo = vk::RenderPassBeginInfo(
			swapchain.getRenderPass(),
			swapchainData->framebuffer,
			vk::Rect2D(
				{ 0, 0 },
				swapchain.getExtent()),
			2,
			clearValues);
		graphicsCommandBuffer.beginRenderPass(
			&renderPassBeginInfo,
			vk::SubpassContents::eInline);
	}
	void VkGpuWindow::endRecord(uint32_t imageIndex)
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
					THIS_FUNCTION_NAME,
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

	std::shared_ptr<CameraEcsSystem> VkGpuWindow::createCameraSystem()
	{
		auto system = std::make_shared<VkCameraEcsSystem>();
		systems.push_back(system);
		return system;
	}
	std::shared_ptr<RenderEcsSystem> VkGpuWindow::createRenderSystem(
		const std::shared_ptr<GpuWindow>& window)
	{
		auto vkWindow = std::dynamic_pointer_cast<VkGpuWindow>(window);
		auto system = std::make_shared<VkRenderEcsSystem>(vkWindow);
		systems.push_back(system);
		return system;
	}

	std::shared_ptr<GpuBuffer> VkGpuWindow::createBuffer(
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

			if(data)
			{
				buffer->setData(
					data,
					size);
			}
		}
		else
		{
			buffer = std::make_shared<VkGpuBuffer>(
				memoryAllocator,
				vk::BufferUsageFlagBits::eTransferDst,
				VMA_MEMORY_USAGE_GPU_ONLY,
				type,
				size);

			if(data)
			{
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
						THIS_FUNCTION_NAME,
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

				if (result != vk::Result::eSuccess)
				{
					throw Exception(
						THIS_FUNCTION_NAME,
						"Failed to submit graphics queue");
				}

				graphicsQueue.waitIdle();

				device.freeCommandBuffers(
					transferCommandPool,
					1,
					&commandBuffer);
			}
		}

		return buffer;
	}
	std::shared_ptr<GpuMesh> VkGpuWindow::createMesh(
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
	std::shared_ptr<ShaderData> VkGpuWindow::readShaderData(
		const std::string& filePath)
	{
		auto fileStream = FileStream(
			filePath + ".spv",
			std::ios::in | std::ios::binary);

		if (!fileStream.is_open())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to open shader file '" +
					std::string(filePath) + "'");
		}

		auto shaderData = std::make_shared<ShaderData>();
		shaderData->code = std::vector<uint8_t>(fileStream.getSize());

		fileStream.read(
			shaderData->code.data(),
			fileStream.getSize());

		return shaderData;
	}
	std::shared_ptr<GpuShader> VkGpuWindow::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		return std::make_shared<VkGpuShader>(device, stage, data);
	}
	std::shared_ptr<GpuImage> VkGpuWindow::createImage(
		GpuImageType type,
		GpuImageFormat format,
		const SizeVector3& size,
		bool useMipmap,
		const void* data)
	{
		auto image = std::make_shared<VkGpuImage>(
			memoryAllocator,
			vk::ImageUsageFlagBits::eTransferDst |
			vk::ImageUsageFlagBits::eSampled,
			type,
			format,
			size);

		if(data)
		{
			auto stagingBufferSize = size.x * size.y *
				getImageFormatComponentCount(format) *
				getImageFormatComponentSize(format);
			auto stagingBuffer = VkGpuBuffer(
				memoryAllocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_ONLY,
				GpuBufferType::TransferSource,
				stagingBufferSize);
			stagingBuffer.setData(
				data,
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
					THIS_FUNCTION_NAME,
					"Failed to allocate command buffer");
			}

			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
			commandBuffer.begin(commandBufferBeginInfo);

			auto firstBarrier = vk::ImageMemoryBarrier(
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
				&firstBarrier);

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
					static_cast<uint32_t>(size.x),
					static_cast<uint32_t>(size.y),
					static_cast<uint32_t>(size.z)));
			commandBuffer.copyBufferToImage(
				stagingBuffer.getBuffer(),
				image->getImage(),
				vk::ImageLayout::eTransferDstOptimal,
				1,
				&bufferImageCopy);

			auto secondBarrier = vk::ImageMemoryBarrier(
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
				&secondBarrier);

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
					THIS_FUNCTION_NAME,
					"Failed to submit graphics queue");
			}

			graphicsQueue.waitIdle();

			device.freeCommandBuffers(
				transferCommandPool,
				1,
				&commandBuffer);
		}
		else
		{
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
					THIS_FUNCTION_NAME,
					"Failed to allocate command buffer");
			}

			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
			commandBuffer.begin(commandBufferBeginInfo);

			auto barrier = vk::ImageMemoryBarrier(
				vk::AccessFlags(),
				vk::AccessFlagBits::eShaderRead,
				vk::ImageLayout::eUndefined,
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
				vk::PipelineStageFlagBits::eTopOfPipe,
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
					THIS_FUNCTION_NAME,
					"Failed to submit graphics queue");
			}

			graphicsQueue.waitIdle();

			device.freeCommandBuffers(
				transferCommandPool,
				1,
				&commandBuffer);
		}

		return image;
	}
	std::shared_ptr<GpuFramebuffer> VkGpuWindow::createFramebuffer(
		const std::shared_ptr<GpuImage>& colorImage,
		const std::shared_ptr<GpuImage>& depthImage,
		const std::shared_ptr<GpuImage>& stencilImage)
	{
		// TODO:
		return nullptr;
	}

	std::shared_ptr<GpuPipeline> VkGpuWindow::createColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& color)
	{
		auto vkVertexShader = std::dynamic_pointer_cast<VkGpuShader>(vertexShader);
		auto vkFragmentShader = std::dynamic_pointer_cast<VkGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<VkColorGpuPipeline>(
			device,
			swapchain.getRenderPass(),
			swapchain.getExtent(),
			drawMode,
			vkVertexShader,
			vkFragmentShader,
			color);

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return pipeline;
	}
	std::shared_ptr<GpuPipeline> VkGpuWindow::createColorColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& color)
	{
		// TODO:
		return nullptr;
	}
	std::shared_ptr<GpuPipeline> VkGpuWindow::createDiffusePipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& objectColor,
		const FloatVector4& ambientColor,
		const FloatVector4& lightColor,
		const FloatVector3& lightDirection)
	{
		auto vkVertexShader = std::dynamic_pointer_cast<VkGpuShader>(vertexShader);
		auto vkFragmentShader = std::dynamic_pointer_cast<VkGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<VkDiffuseGpuPipeline>(
			device,
			memoryAllocator,
			swapchain.getRenderPass(),
			swapchain.getDatas().size(),
			swapchain.getExtent(),
			drawMode,
			vkVertexShader,
			vkFragmentShader,
			VkDiffuseGpuPipeline::UniformBufferObject(
				objectColor,
				ambientColor,
				lightColor,
				lightDirection));

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return pipeline;
	}
	std::shared_ptr<GpuPipeline> VkGpuWindow::createImageDiffusePipeline(
		GpuDrawMode drawMode,
		GpuImageFilter imageMinFilter,
		GpuImageFilter imageMagFilter,
		GpuImageFilter mipmapFilter,
		GpuImageWrap imageWrapU,
		GpuImageWrap imageWrapV,
		GpuImageWrap imageWrapW,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& image,
		const FloatVector4& objectColor,
		const FloatVector4& ambientColor,
		const FloatVector4& lightColor,
		const FloatVector3& lightDirection,
		const FloatVector2& imageScale,
		const FloatVector2& imageOffset)
	{
		auto vkVertexShader = std::dynamic_pointer_cast<VkGpuShader>(vertexShader);
		auto vkFragmentShader = std::dynamic_pointer_cast<VkGpuShader>(fragmentShader);
		auto vkImage = std::dynamic_pointer_cast<VkGpuImage>(image);

		auto pipeline = std::make_shared<VkImageDiffuseGpuPipeline>(
			device,
			memoryAllocator,
			swapchain.getRenderPass(),
			swapchain.getDatas().size(),
			swapchain.getExtent(),
			drawMode,
			imageMinFilter,
			imageMagFilter,
			mipmapFilter,
			imageWrapU,
			imageWrapV,
			imageWrapW,
			vkVertexShader,
			vkFragmentShader,
			vkImage,
			VkImageDiffuseGpuPipeline::UniformBufferObject(
				objectColor,
				ambientColor,
				lightColor,
				lightDirection,
				imageScale,
				imageOffset));

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return pipeline;
	}
	std::shared_ptr<GpuPipeline> VkGpuWindow::createGuiPipeline(
		GpuDrawMode drawMode,
		GpuImageFilter imageMinFilter,
		GpuImageFilter imageMagFilter,
		GpuImageFilter mipmapFilter,
		GpuImageWrap imageWrapU,
		GpuImageWrap imageWrapV,
		GpuImageWrap imageWrapW,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& image,
		const FloatVector2& imageScale,
		const FloatVector2& imageOffset)
	{
		// TODO:
		return nullptr;
	}
	std::shared_ptr<GpuPipeline> VkGpuWindow::createSkyPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		return nullptr;
	}
}
