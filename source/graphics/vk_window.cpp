#include <injector/graphics/vk_window.hpp>

namespace INJECTOR_NAMESPACE
{
#define FRAME_LAG 2

	VkWindow::VkWindow(
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) :
		Window(title, position, size, flags | SDL_WINDOW_VULKAN)
	{
		windowInstance = new VkWindowInstance(window, title, 1);
		surface = new VkSurface(window, windowInstance->getInstance());
		logicalDevice = new VkLogicalDevice(
			surface->getPhysicalDevice(), surface->getSurface());
		swapchain = new VkSwapchain(
			surface->getPhysicalDevice(),
			surface->getSurface(),
			logicalDevice->getDevice(),
			logicalDevice->getGraphicsQueueFamilyIndex(),
			logicalDevice->getPresentQueueFamilyIndex(),
			size);
	}
	VkWindow::~VkWindow()
	{
		delete swapchain;
		swapchain = nullptr;

		delete logicalDevice;
		logicalDevice = nullptr;

		delete surface;
		surface = nullptr;

		delete windowInstance;
		windowInstance = nullptr;
	}
}
