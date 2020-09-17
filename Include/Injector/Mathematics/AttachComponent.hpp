#pragma once
#include "Injector/Component.hpp"
#include "Injector/Entity.hpp"

namespace Injector
{
	struct AttachComponent : public Component
	{
		std::shared_ptr<Entity> target;

		AttachComponent(const std::shared_ptr<Entity>& target = nullptr);
		virtual ~AttachComponent();
	};
}
