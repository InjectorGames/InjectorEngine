#include <injector/graphics/render_system.hpp>
#include <injector/engine.hpp>
#include <injector/graphics/vk_render_system.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	RenderSystem::~RenderSystem()
	{}

	WindowHandle RenderSystem::getWindow() const
	{
		throw std::runtime_error("Not implemented render system function");
	}

	size_t RenderSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}
	size_t RenderSystem::getRenderCount() const noexcept
	{
		return renders.size();
	}

	bool RenderSystem::addCamera(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<CameraComponent>() ||
			!entity->containsComponent<TransformComponent>())
			return false;

		return cameras.emplace(entity).second;
	}
	bool RenderSystem::addRender(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<RenderComponent>())
			return false;

		return renders.emplace(entity).second;
	}

	bool RenderSystem::removeCamera(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	bool RenderSystem::removeRender(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = renders.find(entity);

		if (iterator == renders.end())
			return false;

		renders.erase(iterator);
		return true;
	}

	void RenderSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
	void RenderSystem::removeRenders() noexcept
	{
		renders.clear();
	}

	std::shared_ptr<RenderSystem> RenderSystem::create(const WindowHandle& window)
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		if (graphicsAPI == GraphicsAPI::OpenGL)
			return nullptr;
		else if (graphicsAPI == GraphicsAPI::OpenGLES)
			return nullptr;
		else if (graphicsAPI == GraphicsAPI::Vulkan)
			return window->createSystem<VkRenderSystem>(
				std::dynamic_pointer_cast<VkWindow>(window));
		else
			throw std::runtime_error("Failed to create render system, unknown graphics API");
	}
}
