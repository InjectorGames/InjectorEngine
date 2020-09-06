#pragma once
#include "Injector/Component.hpp"
#include "Injector/Entity.hpp"

namespace Injector::Mathematics
{
	struct AttachComponent : public Component
	{
		shared_ptr<Entity> target;

		AttachComponent(const shared_ptr<Entity>& target = nullptr);
		virtual ~AttachComponent();
	};
}
