#include <injector/render_system.hpp>
#include <injector/window_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderSystem::RenderSystem(
		Manager& manager,
		const EntityHandle& _window) :
		System(manager),
		window(_window)
	{}
	RenderSystem::~RenderSystem()
	{}

	void RenderSystem::update()
	{
		if (window != nullptr)
		{
			WindowComponent* windowComponent;

			if(window->getComponent<WindowComponent>(windowComponent))
			{
				auto windowHandle = windowComponent->window;
				windowHandle->setContext();
				windowHandle->swapChain();
			}
		}
	}
}
