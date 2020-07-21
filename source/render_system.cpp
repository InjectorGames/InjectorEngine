#include <injector/render_system.hpp>
#include <injector/window_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderSystem::RenderSystem(const EntityHandle& _window) :
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
