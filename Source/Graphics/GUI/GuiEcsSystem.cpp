#include "Injector/Graphics/GUI/GuiEcsSystem.hpp"

namespace Injector
{
	GuiEcsSystem::GuiEcsSystem(
		const std::shared_ptr<GpuWindow>& _window) noexcept :
		window(_window),
		guis()
	{
	}

	size_t GuiEcsSystem::getGuiCount() const noexcept
	{
		return guis.size();
	}

	void GuiEcsSystem::update()
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

			if(guiComponent->fixedScale)
			{
				auto guiScale = guiComponent->scale;
				auto framebufferSize = window->getFramebufferSize();

				transformComponent->scale = Vector3(
					(guiScale.x * std::abs(frustum.x - frustum.y)) /
						(framebufferSize.x / aspectRatio),
					(guiScale.y * std::abs(frustum.z - frustum.w)) /
						framebufferSize.y,
					guiScale.z);
			}
			else
			{
				transformComponent->scale = guiComponent->scale;
			}
		}
	}

	bool GuiEcsSystem::addGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return guis.emplace(entity).second;
	}
	bool GuiEcsSystem::removeGui(
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
	void GuiEcsSystem::removeGuis() noexcept
	{
		guis.clear();
	}
}
