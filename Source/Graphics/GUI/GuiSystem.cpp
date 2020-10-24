#include "Injector/Graphics/GUI/GuiSystem.hpp"

namespace Injector
{
	GuiSystem::GuiSystem() noexcept :
		guis()
	{
	}

	size_t GuiSystem::getGuiCount() const noexcept
	{
		return guis.size();
	}

	void GuiSystem::update()
	{
		CameraEcsComponent* cameraComponent;

		if(!camera || !camera->getComponent(cameraComponent))
			return;

		auto frustum = cameraComponent->frustum;
		auto aspectRatio = cameraComponent->aspectRatio;

		for (auto& gui : guis)
		{
			GuiEcsComponent* guiComponent;
			TransformEcsComponent* transformComponent;

			if (!gui->getComponent(guiComponent) ||
				!gui->getComponent(transformComponent))
				continue;

			auto guiPosition = guiComponent->position;

			switch (guiComponent->anchor)
			{
			case GuiAnchorType::Center:
				transformComponent->position = guiPosition;
				break;
			case GuiAnchorType::Left:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y,
					guiPosition.z);
				break;
			case GuiAnchorType::Right:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y,
					guiPosition.z);
				break;
			case GuiAnchorType::Bottom:
				transformComponent->position = Vector3(
					guiPosition.x,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::Top:
				transformComponent->position = Vector3(
					guiPosition.x,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			case GuiAnchorType::LeftBottom:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::LeftTop:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			case GuiAnchorType::RightBottom:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::RightTop:
				transformComponent->position = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			}

			guiComponent->rotation = guiComponent->rotation;

			// TODO: fixed scale transforms
		}
	}

	bool GuiSystem::addGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return guis.emplace(entity).second;
	}
	bool GuiSystem::removeGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = guis.find(entity);

		if (iterator == guis.end())
			return false;

		guis.erase(iterator);
		return true;
	}
	void GuiSystem::removeGuis() noexcept
	{
		guis.clear();
	}
}
