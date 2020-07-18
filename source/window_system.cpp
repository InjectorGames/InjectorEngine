#include <injector/window_system.hpp>
#include <injector/engine.hpp>

#include <string>

namespace INJECTOR_NAMESPACE
{
	WindowSystem::WindowSystem(Manager& manager) :
		System(manager),
		windows()
	{}
	WindowSystem::~WindowSystem()
	{
		destroyWindows();
	}

	void WindowSystem::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			for (auto id : windows)
			{
				WindowComponent* windowComponent;

				if (manager.getComponent(id, windowComponent))
				{
					auto win = windowComponent->window;
				}
			}
		}
	}

	bool WindowSystem::createWindow(Entity entity) noexcept
	{
		if (manager != entity.manager)
			return false;

		auto graphicsAPI = Engine::getGraphicsAPI();
		uint32_t flags = SDL_WINDOW_RESIZABLE;

		switch (graphicsAPI)
		{
		case injector::GraphicsAPI::OpenGL:
			flags |= SDL_WINDOW_OPENGL;
			break;
		case injector::GraphicsAPI::Vulkan:
			flags |= SDL_WINDOW_VULKAN;
			break;
		default:
			return false;
		}

		auto window = SDL_CreateWindow(INJECTOR_WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			INJECTOR_WINDOW_WIDTH, INJECTOR_WINDOW_HEIGHT, flags);

		if (window == nullptr)
			throw false;

		WindowComponent* windowComponent;

		if (!entity.createComponent<WindowComponent>(windowComponent))
		{
			SDL_DestroyWindow(window);
			throw false;
		}

		if (!windows.emplace(entity.id).second)
		{
			entity.destroyComponent<WindowComponent>();
			SDL_DestroyWindow(window);
			throw false;
		}

		return true;
	}
	bool WindowSystem::destroyWindow(Entity entity) noexcept
	{
		if (manager != entity.manager)
			return false;

		if (windows.find(entity.id) == windows.end())
			return false;

		WindowComponent* windowComponent;

		if (!entity.getComponent<WindowComponent>(windowComponent))
			return false;

		SDL_DestroyWindow(windowComponent->window);
		entity.destroyComponent<WindowComponent>();
		return true;
	}
	void WindowSystem::destroyWindows() noexcept
	{
		for (auto id : windows)
		{
			WindowComponent* component;

			if (!manager.getComponent<WindowComponent>(id, component))
				continue;

			SDL_DestroyWindow(component->window);
			manager.destroyComponent<WindowComponent>(id);
		}
	}
}
