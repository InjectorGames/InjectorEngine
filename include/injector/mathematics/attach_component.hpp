#pragma once
#include <injector/component.hpp>
#include <injector/entity.hpp>

namespace INJECTOR_NAMESPACE
{
	struct AttachComponent : public Component
	{
		EntityHandle target;

		AttachComponent(const EntityHandle& target = nullptr);
		virtual ~AttachComponent();
	};
}
