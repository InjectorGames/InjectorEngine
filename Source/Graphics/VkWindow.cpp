#include "Injector/Graphics/VkWindow.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Graphics/VkGpuMesh.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/VkCameraSystem.hpp"
#include "Injector/Graphics/VkRenderSystem.hpp"
#include "Injector/Graphics/Pipeline/VkColorGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/VkDiffuseGpuPipeline.hpp"

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
			std::cout << "VULKAN VERBOSE: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
			std::cout << "VULKAN INFO: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			std::cout << "VULKAN WARNING: " << pCallbackData->pMessage << "\n";
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			std::cout << "VULKAN ERROR: " << pCallbackData->pMessage << "\n";

		return VK_FALSE;
	}

	GLFWwindow* VkWindow::createWindow(
		const std::string& title,
		const IntVector2& size)
	{
		glfwDefaultWindowHints();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		return glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	}
	vk::Instance VkWindow::createInstance(
		const std::string& appName,
		uint32_t appVersion)
	{
		vk::Instance instance;

		auto instanceLayers = std::vector<const char*>();

#if !defined(NDEBUG)
		instanceLayers.push_back("VK_LAYER_KHRONOS_validation");

		auto instanceLayerProperties = vk::enumerateInstanceLayerProperties();

		if (instanceLayerProperties.size() == 0)
			throw Exception("VkWindow", "createInstance", "Failed to get instance layer properties");

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
				throw Exception("VkWindow", "createInstance",
					"Failed to get instance layer \"" + std::string(layer) + "\"");
			}
		}
#endif
		
		uint32_t extensionCount;
		auto glfwInstanceExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

		if (extensionCount == 0)
			throw Exception("VkWindow", "createInstance", "Failed to get instance extensions");

		auto instanceExtensions = std::vector<const char*>();

		for (size_t i = 0; i < extensionCount; i++)
			instanceExtensions.push_back(glfwInstanceExtensions[i]);
		

#if !defined(NDEBUG)
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		auto instanceExtensionProperties = vk::enumerateInstanceExtensionProperties();

		if (instanceExtensionProperties.size() == 0)
			throw Exception("VkWindow", "createInstance", "Failed to get instance extension properties");

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
				throw Exception("VkWindow", "createInstance",
					"Failed to get instance extension \"" + std::string(extension) + "\"");
			}
		}

		auto applicationInfo = vk::ApplicationInfo(
			appName.c_str(), appVersion,
			"Injector Engine",
			VK_MAKE_VERSION(
				INJECTOR_VERSION_MAJOR, 
				INJECTOR_VERSION_MINOR,
				INJECTOR_VERSION_PATCH),
			VK_API_VERSION_1_0);

		auto instanceCreateInfo = vk::InstanceCreateInfo({}, &applicationInfo,
			static_cast<uint32_t>(instanceLayers.size()), instanceLayers.data(),
			static_cast<uint32_t>(instanceExtensions.size()), instanceExtensions.data());

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
		auto reslut = vk::createInstance(&instanceCreateInfo, nullptr, &instance);

		if (reslut != vk::Result::eSuccess)
			throw Exception("VkWindow", "createInstance", "Failed to create instance");

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
			&debugUtilsMessengerCreateInfo, nullptr, &debugMessenger, dispatchDynamic);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createDebugMessenger", "Failed to create debug messenger");

		return debugMessenger;
#else
		return nullptr;
#endif
	}
	vk::PhysicalDevice VkWindow::getBestPhysicalDevice(
		vk::Instance instance)
	{
		auto physicalDevices = instance.enumeratePhysicalDevices();

		if (physicalDevices.size() == 0)
			throw Exception("VkWindow", "getBestPhysicalDevice", "Failed to get physical devices");

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

		return targetPhysicalDevices.rbegin()->second;
	}
	vk::SurfaceKHR VkWindow::createSurface(
		vk::Instance instance,
		GLFWwindow* window)
	{
		VkSurfaceKHR surfaceHandle;
		auto result = glfwCreateWindowSurface(instance, window, NULL, &surfaceHandle);

		if (result != VK_SUCCESS)
			throw Exception("VkWindow", "createSurface", "Failed to create surface");

		return vk::SurfaceKHR(surfaceHandle);
	}
	void VkWindow::getQueueFamilyIndices(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface,
		uint32_t& graphicsQueueFamilyIndex,
		uint32_t& presentQueueFamilyIndex)
	{
		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

		if (queueFamilyProperties.size() == 0)
			throw Exception("VkWindow", "getQueueFamilyIndices", "Failed to get queue family properties");

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
			throw Exception("VkWindow", "getQueueFamilyIndices", "Failed to find graphics queue family");
		if (presentQueueFamilyIndex == UINT32_MAX)
			throw Exception("VkWindow", "getQueueFamilyIndices", "Failed to find present queue family");
	}
	vk::Device VkWindow::createDevice(
		vk::PhysicalDevice physicalDevice,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex)
	{
		vk::Device device;

		auto deviceExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();

		if (deviceExtensionProperties.size() == 0)
			throw Exception("VkWindow", "createDevice", "Failed to get device extension properties");

		// TODO: create extension request mechanism
		auto deviceExtensions = std::vector<const char*>() =
		{
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
				throw Exception("VkWindow", "createDevice",
					"Failed to find device extension \"" + std::string(extension) + "\"");
			}
		}

		auto priority = 1.0f;
		auto deviceQueueCreateInfo = vk::DeviceQueueCreateInfo(
			{}, graphicsQueueFamilyIndex, 1, &priority);

		auto deviceQueueCreateInfos = std::vector<vk::DeviceQueueCreateInfo>() =
		{
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
			0, nullptr,
			static_cast<uint32_t>(deviceExtensions.size()),
			deviceExtensions.data(),
			nullptr);

		auto result = physicalDevice.createDevice(&deviceCreateInfo, nullptr, &device);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createDevice", "Failed to create device");

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
			throw Exception("VkWindow", "createMemoryAllocator", "Failed to create memory allocator");

		return allocator;
	}
	vk::Fence VkWindow::createFence(
		vk::Device device,
		vk::FenceCreateFlags flags)
	{
		vk::Fence fence;

		auto fenceCreateInfo = vk::FenceCreateInfo(flags);
		auto result = device.createFence(&fenceCreateInfo, nullptr, &fence);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createFence", "Failed to create fence");

		return fence;
	}
	vk::Semaphore VkWindow::createSemaphore(
		vk::Device device,
		vk::SemaphoreCreateFlags flags)
	{
		vk::Semaphore semaphore;

		auto fenceCreateInfo = vk::SemaphoreCreateInfo(flags);
		auto result = device.createSemaphore(&fenceCreateInfo, nullptr, &semaphore);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createSemaphore", "Failed to create semaphore");

		return semaphore;
	}
	vk::Queue VkWindow::getQueue(
		vk::Device device,
		uint32_t queueFamilyIndex,
		uint32_t queueIndex)
	{
		auto queue = device.getQueue(queueFamilyIndex, queueIndex);

		if (!queue)
			throw Exception("VkWindow", "getQueue", "Failed to get queue");

		return queue;
	}
	uint32_t VkWindow::getBestSurfaceImageCount(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		auto imageCount = surfaceCapabilities.minImageCount + 1;

		if (surfaceCapabilities.maxImageCount > 0 &&
			imageCount > surfaceCapabilities.maxImageCount)
			imageCount = surfaceCapabilities.maxImageCount;

		return imageCount;
	}
	vk::SurfaceFormatKHR VkWindow::getBestSurfaceFormat(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface)
	{
		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
			throw Exception("VkWindow", "getBestSurfaceFormat", "Failed to get surface formats");

		auto surfaceFormat = surfaceFormats[0];

		for (auto& format : surfaceFormats)
		{
			if (format.format == vk::Format::eB8G8R8A8Srgb &&
				format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				surfaceFormat = format;
				break;
			}
		}

		if (surfaceFormat == vk::Format::eUndefined)
			surfaceFormat = vk::Format::eB8G8R8A8Srgb;

		return surfaceFormat;
	}
	vk::PresentModeKHR VkWindow::getBestSurfacePresentMode(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface)
	{
		auto surfacePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

		if (surfacePresentModes.size() == 0)
			throw Exception("VkWindow", "getBestSurfacePresentMode", "Failed to get surface present modes");

		auto presentMode = vk::PresentModeKHR::eFifo;

		// TODO: Test all modes to pick best
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eMailbox)
			{
				presentMode = mode;
				break;
			}
		}
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eFifoRelaxed)
			{
				presentMode = mode;
				break;
			}
		}
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eImmediate)
			{
				presentMode = mode;
				break;
			}
		}

		return presentMode;
	}
	vk::SurfaceTransformFlagBitsKHR VkWindow::getBestSurfaceTransform(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		if (surfaceCapabilities.supportedTransforms & 
			vk::SurfaceTransformFlagBitsKHR::eIdentity)
		{
			return vk::SurfaceTransformFlagBitsKHR::eIdentity;
		}
		else
		{
			return surfaceCapabilities.currentTransform;
		}
	}
	vk::CompositeAlphaFlagBitsKHR VkWindow::getBestSurfaceCompositeAlpha(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::eOpaque)
			return vk::CompositeAlphaFlagBitsKHR::eOpaque;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
			return vk::CompositeAlphaFlagBitsKHR::ePreMultiplied;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
			return vk::CompositeAlphaFlagBitsKHR::ePostMultiplied;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::eInherit)
			return vk::CompositeAlphaFlagBitsKHR::eInherit;
		else
			throw Exception("VkWindow", "getBestSurfaceCompositeAlpha", "Failed to get surface composite alpha");
	}
	vk::Extent2D VkWindow::getBestSurfaceExtent(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
		IntVector2 surfaceSize)
	{
		if (surfaceCapabilities.currentExtent.width == UINT32_MAX)
		{
			return vk::Extent2D(
				std::clamp(static_cast<uint32_t>(surfaceSize.x), 
				surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width),
				std::clamp(static_cast<uint32_t>(surfaceSize.x), 
				surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width));
		}
		else
		{
			return surfaceCapabilities.currentExtent;
		}
	}
	vk::SwapchainKHR VkWindow::createSwapchain(
		vk::Device device,
		vk::SurfaceKHR surface,
		uint32_t surfaceImageCount,
		vk::SurfaceFormatKHR surfaceFormat,
		vk::Extent2D surfaceExtent,
		vk::SurfaceTransformFlagBitsKHR surfaceTransform,
		vk::CompositeAlphaFlagBitsKHR surfaceCompositeAlpha,
		vk::PresentModeKHR surfacePresentMode)
	{
		vk::SwapchainKHR swapchain;

		auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR({},
			surface,
			surfaceImageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			surfaceExtent,
			1, vk::ImageUsageFlagBits::eColorAttachment,
			vk::SharingMode::eExclusive,
			0, nullptr,
			surfaceTransform,
			surfaceCompositeAlpha,
			surfacePresentMode,
			true,
			nullptr);

		auto result = device.createSwapchainKHR(&swapchainCreateInfo, nullptr, &swapchain);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createSwapchain", "Failed to create swapchain");

		return swapchain;
	}
	vk::RenderPass VkWindow::createRenderPass(
		vk::Device device,
		vk::Format format)
	{
		vk::RenderPass renderPass;

		auto colorAttachmentDescription = vk::AttachmentDescription({},
			format,
			vk::SampleCountFlagBits::e1,
			vk::AttachmentLoadOp::eClear,
			vk::AttachmentStoreOp::eStore,
			vk::AttachmentLoadOp::eDontCare,
			vk::AttachmentStoreOp::eDontCare,
			vk::ImageLayout::eUndefined,
			vk::ImageLayout::ePresentSrcKHR);

		auto colorAttachmentReference = vk::AttachmentReference(
			0, vk::ImageLayout::eColorAttachmentOptimal);


		auto subpassDescription = vk::SubpassDescription({},
			vk::PipelineBindPoint::eGraphics,
			0, nullptr,
			1, &colorAttachmentReference);

		// TODO: make good loking
		vk::SubpassDependency dependency {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		dependency.srcAccessMask = {};
		dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

		auto renderPassCreateInfo = vk::RenderPassCreateInfo({},
			1, &colorAttachmentDescription,
			1, &subpassDescription, 
			1, &dependency);

		auto result = device.createRenderPass(&renderPassCreateInfo, nullptr, &renderPass);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createRenderPass", "Failed to create render pass");

		return renderPass;
	}
	vk::CommandPool VkWindow::createCommandPool(
		vk::Device device,
		vk::CommandPoolCreateFlags flags,
		uint32_t queueFamilyIndex)
	{
		vk::CommandPool commandPool;

		auto commandPoolCreateInfo = vk::CommandPoolCreateInfo(
			flags, queueFamilyIndex);
		auto result = device.createCommandPool(
			&commandPoolCreateInfo, nullptr, &commandPool);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "createCommandPool", "Failed to create command pool");

		return commandPool;
	}

	VkWindow::VkWindow(
		const std::string& title,
		const IntVector2& size,
		bool stereo) :
		Window(createWindow(title, size))
	{
		// TODO: stereo rendering

		instance = createInstance(title.c_str(), 1);

		try
		{
			dispatchDynamic = vk::DispatchLoaderDynamic(
				static_cast<VkInstance>(instance), vkGetInstanceProcAddr);
			debugMessenger = createDebugMessenger(
				instance, dispatchDynamic);

			physicalDevice = getBestPhysicalDevice(instance);
			surface = createSurface(instance, window);

			getQueueFamilyIndices(physicalDevice, surface,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex);

			device = createDevice(physicalDevice,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex);
			memoryAllocator = createMemoryAllocator(
				instance, physicalDevice, device);

			fences = std::vector<vk::Fence>(VK_FRAME_LAG);
			imageAcquiredSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);
			drawCompleteSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);
			imageOwnershipSemaphores = std::vector<vk::Semaphore>(VK_FRAME_LAG);

			for (size_t i = 0; i < VK_FRAME_LAG; i++)
			{
				fences[i] = createFence(device, vk::FenceCreateFlagBits::eSignaled);
				imageAcquiredSemaphores[i] = createSemaphore(device, {});
				drawCompleteSemaphores[i] = createSemaphore(device, {});
				imageOwnershipSemaphores[i] = createSemaphore(device, {});
			}

			graphicsQueue = getQueue(device, graphicsQueueFamilyIndex, 0);
			presentQueue = getQueue(device, presentQueueFamilyIndex, 0);

			if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
			{
				graphicsCommandPool = createCommandPool(device, 
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
					graphicsQueueFamilyIndex);
				presentCommandPool = createCommandPool(device,
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer, 
					presentQueueFamilyIndex);
			}
			else
			{
				graphicsCommandPool = presentCommandPool = createCommandPool(device, 
					vk::CommandPoolCreateFlagBits::eTransient |
					vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
					graphicsQueueFamilyIndex);
			}

			transferCommandPool = createCommandPool(device,
				vk::CommandPoolCreateFlagBits::eTransient,
				graphicsQueueFamilyIndex);

			auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
			auto surfaceImageCount = getBestSurfaceImageCount(surfaceCapabilities);
			auto surfaceFormat = getBestSurfaceFormat(physicalDevice, surface);
			auto surfaceTransform = getBestSurfaceTransform(surfaceCapabilities);
			auto surfaceCompositeAlpha = getBestSurfaceCompositeAlpha(surfaceCapabilities);
			auto surfacePresentMode = getBestSurfacePresentMode(physicalDevice, surface);

			surfaceExtent = getBestSurfaceExtent(
				surfaceCapabilities, size);
			swapchain = createSwapchain(
				device,
				surface,
				surfaceImageCount,
				surfaceFormat,
				surfaceExtent,
				surfaceTransform,
				surfaceCompositeAlpha,
				surfacePresentMode);
			renderPass = createRenderPass(
				device, surfaceFormat.format);

			frameIndex = 0;

			auto images = device.getSwapchainImagesKHR(swapchain);
			swapchainDatas = std::vector<std::shared_ptr<VkSwapchainData>>(images.size());

			for (size_t i = 0; i < images.size(); i++)
			{
				swapchainDatas[i] = std::make_shared<VkSwapchainData>(
					device,
					images[i],
					renderPass,
					graphicsCommandPool,
					presentCommandPool,
					surfaceFormat.format,
					surfaceExtent);
			}
		}
		catch (const std::exception& exception)
		{
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
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
		swapchainDatas.clear();

		device.destroyRenderPass(renderPass);
		device.destroySwapchainKHR(swapchain);
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

		for (uint32_t i = 0; i < VK_FRAME_LAG; i++)
		{
			device.waitForFences(1, &fences[i], VK_TRUE, UINT64_MAX);
			device.destroyFence(fences[i]);
			device.destroySemaphore(imageAcquiredSemaphores[i]);
			device.destroySemaphore(drawCompleteSemaphores[i]);
			device.destroySemaphore(imageOwnershipSemaphores[i]);
		}

		device.waitIdle();
		device.destroy();

		instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
		instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
		instance.destroy();
#endif
	}

	vk::CommandBuffer VkWindow::getGraphicsCommandBuffer(uint32_t imageIndex) const
	{
		return swapchainDatas.at(imageIndex)->graphicsCommandBuffer;
	}
	vk::CommandBuffer VkWindow::getPresentCommandBuffer(uint32_t imageIndex) const
	{
		return swapchainDatas.at(imageIndex)->presentCommandBuffer;
	}

	void VkWindow::onFramebufferResize(const IntVector2& size)
	{
		device.waitIdle();

		swapchainDatas.clear();

		device.destroyRenderPass(renderPass);
		device.destroySwapchainKHR(swapchain);

		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
		auto surfaceImageCount = getBestSurfaceImageCount(surfaceCapabilities);
		auto surfaceFormat = getBestSurfaceFormat(physicalDevice, surface);
		auto surfaceTransform = getBestSurfaceTransform(surfaceCapabilities);
		auto surfaceCompositeAlpha = getBestSurfaceCompositeAlpha(surfaceCapabilities);
		auto surfacePresentMode = getBestSurfacePresentMode(physicalDevice, surface);

		surfaceExtent = getBestSurfaceExtent(
			surfaceCapabilities, size);
		swapchain = createSwapchain(
			device,
			surface,
			surfaceImageCount,
			surfaceFormat,
			surfaceExtent,
			surfaceTransform,
			surfaceCompositeAlpha,
			surfacePresentMode);
		renderPass = createRenderPass(
			device, surfaceFormat.format);

		frameIndex = 0;

		auto images = device.getSwapchainImagesKHR(swapchain);
		swapchainDatas = std::vector<std::shared_ptr<VkSwapchainData>>(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{
			swapchainDatas[i] = std::make_shared<VkSwapchainData>(
				device,
				images[i],
				renderPass,
				graphicsCommandPool,
				presentCommandPool,
				surfaceFormat.format,
				surfaceExtent);
		}

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
			pipeline->recreate(memoryAllocator, renderPass, images.size(), surfaceExtent);
	}

	uint32_t VkWindow::beginImage()
	{
		device.waitForFences(1, &fences[frameIndex], true, UINT64_MAX);
		device.resetFences({ fences[frameIndex] });

		vk::Result result;
		uint32_t imageIndex;

		do
		{
			result = device.acquireNextImageKHR(swapchain, UINT64_MAX,
				imageAcquiredSemaphores[frameIndex], vk::Fence(), &imageIndex);

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
			else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
			{
				throw Exception("VkWindow", "beginImage", "Failed to acquire next image");
			}
		}
		while (result != vk::Result::eSuccess);

		vmaSetCurrentFrameIndex(memoryAllocator, imageIndex);
		return imageIndex;
	}
	void VkWindow::endImage(uint32_t imageIndex)
	{
		vk::PipelineStageFlags waitDestinationStageMask =
			vk::PipelineStageFlagBits::eColorAttachmentOutput;

		auto submitInfo = vk::SubmitInfo(
			1, &imageAcquiredSemaphores[frameIndex],
			&waitDestinationStageMask,
			1, &swapchainDatas[imageIndex]->graphicsCommandBuffer,
			1, &drawCompleteSemaphores[frameIndex]);

		auto result = graphicsQueue.submit(1, &submitInfo, fences[frameIndex]);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "endImage", "Failed to submit graphics queue");

		auto presentInfo = vk::PresentInfoKHR(
			1, &drawCompleteSemaphores[frameIndex],
			1, &swapchain,
			&imageIndex);

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			submitInfo.pWaitSemaphores = &drawCompleteSemaphores[frameIndex];
			submitInfo.pCommandBuffers = &swapchainDatas[imageIndex]->presentCommandBuffer;
			submitInfo.pSignalSemaphores = &imageOwnershipSemaphores[frameIndex];

			result = presentQueue.submit(1, &submitInfo, vk::Fence());

			if (result != vk::Result::eSuccess)
				throw Exception("VkWindow", "endImage", "Failed to submit present queue");

			presentInfo.pWaitSemaphores = &imageOwnershipSemaphores[frameIndex];
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
		else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
		{
			throw Exception("VkWindow", "endImage", "Failed to present next image");
		}
	}

	void VkWindow::beginRecord(uint32_t imageIndex)
	{
		auto& swapchainData = swapchainDatas[imageIndex];
		auto graphicsCommandBuffer = swapchainData->graphicsCommandBuffer;

		auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
			vk::CommandBufferUsageFlagBits::eOneTimeSubmit, nullptr);
		auto result = graphicsCommandBuffer.begin(&commandBufferBeginInfo);

		if (result != vk::Result::eSuccess)
			throw Exception("VkWindow", "beginRecord", "Failed to begin command buffer");

		auto clearValues = vk::ClearValue(vk::ClearColorValue(
			std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}));
		auto renderPassBeginInfo = vk::RenderPassBeginInfo(
			renderPass, swapchainData->framebuffer,
			vk::Rect2D({ 0, 0 }, surfaceExtent),
			1, &clearValues);
		graphicsCommandBuffer.beginRenderPass(
			&renderPassBeginInfo, vk::SubpassContents::eInline);
	}
	void VkWindow::endRecord(uint32_t imageIndex)
	{
		auto& swapchainData = swapchainDatas[imageIndex];
		auto graphicsCommandBuffer = swapchainData->graphicsCommandBuffer;
		graphicsCommandBuffer.endRenderPass();

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			auto imageMemoryBarrier = vk::ImageMemoryBarrier({}, {},
				vk::ImageLayout::ePresentSrcKHR, vk::ImageLayout::ePresentSrcKHR,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex, swapchainData->image,
				vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
			graphicsCommandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::PipelineStageFlagBits::eBottomOfPipe,
				{}, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
		}

		graphicsCommandBuffer.end();

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			auto presentCommandBuffer = swapchainData->presentCommandBuffer;
			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eSimultaneousUse, nullptr);
			auto result = presentCommandBuffer.begin(&commandBufferBeginInfo);

			if (result != vk::Result::eSuccess)
				throw Exception("VkWindow", "endRecord", "Failed to begin command buffer");

			auto imageMemoryBarrier = vk::ImageMemoryBarrier({}, {},
				vk::ImageLayout::ePresentSrcKHR, vk::ImageLayout::ePresentSrcKHR,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex, swapchainData->image,
				vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
			presentCommandBuffer.pipelineBarrier(
				vk::PipelineStageFlagBits::eBottomOfPipe,
				vk::PipelineStageFlagBits::eBottomOfPipe,
				{}, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);

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

		if(mappable)
		{
			buffer = std::make_shared<VkGpuBuffer>(
				type, size, memoryAllocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_TO_GPU);
			buffer->setData(data, size);
		}
		else
		{
			buffer = std::make_shared<VkGpuBuffer>(
				type, size, memoryAllocator,
				vk::BufferUsageFlagBits::eTransferDst,
				VMA_MEMORY_USAGE_GPU_ONLY);

			auto stagingBuffer = VkGpuBuffer(
				type, size, memoryAllocator,
				vk::BufferUsageFlagBits::eTransferSrc,
				VMA_MEMORY_USAGE_CPU_ONLY);
			stagingBuffer.setData(data, size);

			vk::CommandBuffer commandBuffer;

			auto commandBufferAlocateInfo = vk::CommandBufferAllocateInfo(
				transferCommandPool, vk::CommandBufferLevel::ePrimary, 1);
			auto result = device.allocateCommandBuffers(
				&commandBufferAlocateInfo, &commandBuffer);

			if (result != vk::Result::eSuccess)
				throw Exception("VkWindow", "createBuffer", "Failed to allocate command buffer");

			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
				vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
			commandBuffer.begin(commandBufferBeginInfo);

			auto bufferCopy = vk::BufferCopy(0, 0, size);
			commandBuffer.copyBuffer(
				stagingBuffer.getBuffer(), buffer->getBuffer(), 1, &bufferCopy);

			commandBuffer.end();

			auto submitInfo = vk::SubmitInfo(0, nullptr, nullptr, 1, &commandBuffer);
			graphicsQueue.submit(1, &submitInfo, nullptr);

			graphicsQueue.waitIdle();
			device.freeCommandBuffers(transferCommandPool, 1, &commandBuffer);
		}

		return buffer;
	}
	std::shared_ptr<GpuMesh> VkWindow::createMesh(
		size_t indexCount,
		GpuBufferIndex indexType,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer)
	{
		return std::make_shared<VkGpuMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
	}
	std::shared_ptr<ShaderData> VkWindow::readShaderData(
		const std::string& filePath)
	{
		auto fileStream = FileStream(filePath, std::ios::in | std::ios::binary);
		auto shaderData = std::make_shared<ShaderData>();
		shaderData->code = std::vector<uint8_t>(fileStream.getSize());
		fileStream.read(shaderData->code.data(), fileStream.getSize());
		return shaderData;
	}
	std::shared_ptr<GpuShader> VkWindow::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		return nullptr;
	}

	/*std::shared_ptr<ColorPipeline> VkWindow::createColorPipeline()
	{
		auto pipeline = std::make_shared<VkColorPipeline>(
			device, renderPass, surfaceExtent);

		if(!pipelines.emplace(pipeline).second)
			throw Exception("VkWindow", "createColorPipeline", "Failed to add pipeline");

		return pipeline;
	}
	std::shared_ptr<DiffusePipeline> VkWindow::createDiffusePipeline()
	{
		auto pipeline = std::make_shared<VkDiffusePipeline>(
			device, memoryAllocator, renderPass, swapchainDatas.size(), surfaceExtent);

		if (!pipelines.emplace(pipeline).second)
			throw Exception("VkWindow", "createDiffusePipeline", "Failed to add pipeline");

		return pipeline;
	}*/
}
