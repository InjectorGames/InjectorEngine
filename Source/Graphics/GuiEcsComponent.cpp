#include "Injector/Graphics/GuiEcsComponent.hpp"

namespace Injector
{
	GuiEcsComponent::GuiEcsComponent(
		const std::shared_ptr<GuiHandler>& _handler) noexcept :
		handler(_handler)
	{
	}
}
