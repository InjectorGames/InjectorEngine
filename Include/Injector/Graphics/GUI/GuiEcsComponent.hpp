#pragma once
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/Mathematics/Vector/Vector3.hpp"
#include "Injector/Graphics/GUI/GuiHandler.hpp"
#include "Injector/Graphics/GUI/GuiAnchorType.hpp"

#include <memory>

namespace Injector
{
	struct GuiEcsComponent final : public EcsComponent
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		GuiAnchorType anchor;
		bool fixedScale;
		std::shared_ptr<EcsEntity> parent;
		std::shared_ptr<GuiHandler> handler;

		explicit GuiEcsComponent(
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion::zero,
			const Vector3& scale = Vector3::one,
			GuiAnchorType anchor = GuiAnchorType::Center,
			bool fixedScale = false,
			const std::shared_ptr<EcsEntity>& parent = nullptr,
			const std::shared_ptr<GuiHandler>& handler = nullptr);
	};
}
