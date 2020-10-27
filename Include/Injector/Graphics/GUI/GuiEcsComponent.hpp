#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/Mathematics/Vector/Vector3.hpp"
#include "Injector/Graphics/GUI/GuiHandler.hpp"
#include "Injector/Graphics/GUI/GuiAnchorType.hpp"

namespace Injector
{
	struct GuiEcsComponent final : public EcsComponent
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		GuiAnchorType anchor;
		bool fixedScale;
		std::shared_ptr<GuiHandler> handler;

		explicit GuiEcsComponent(
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion(Vector3::zero),
			const Vector3& scale = Vector3::one,
			GuiAnchorType anchor = GuiAnchorType::Center,
			bool fixedScale = false,
			const std::shared_ptr<GuiHandler>& handler = nullptr);
	};
}
