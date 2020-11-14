#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Graphics/GuiHandler.hpp"

#include <memory>

namespace Injector
{
	struct GuiEcsComponent final : public EcsComponent
	{
		std::shared_ptr<GuiHandler> handler;

		explicit GuiEcsComponent(
			const std::shared_ptr<GuiHandler>& handler) noexcept;
	};
}
