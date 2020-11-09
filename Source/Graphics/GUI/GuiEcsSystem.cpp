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

			if(guiComponent->handler)
			{
				auto handler = guiComponent->handler;
				handler->update();


			}

			auto guiPosition = guiComponent->position;

			switch (guiComponent->anchor)
			{
			default:
				break;
			case GuiAnchorType::Left:
				guiPosition = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y,
					guiPosition.z);
				break;
			case GuiAnchorType::Right:
				guiPosition = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y,
					guiPosition.z);
				break;
			case GuiAnchorType::Bottom:
				guiPosition = Vector3(
					guiPosition.x,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::Top:
				guiPosition = Vector3(
					guiPosition.x,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			case GuiAnchorType::LeftBottom:
				guiPosition = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::LeftTop:
				guiPosition = Vector3(
					guiPosition.x + frustum.x * aspectRatio,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			case GuiAnchorType::RightBottom:
				guiPosition = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y + frustum.z,
					guiPosition.z);
				break;
			case GuiAnchorType::RightTop:
				guiPosition = Vector3(
					guiPosition.x + frustum.y * aspectRatio,
					guiPosition.y + frustum.w,
					guiPosition.z);
				break;
			}

			if(guiComponent->fixedScale)
			{
				auto framebufferSize = window->getFramebufferSize();

				transformComponent->position = Vector3(
					(guiPosition.x * std::abs(frustum.x - frustum.y)) /
						(static_cast<float>(framebufferSize.x) / aspectRatio),
					(guiPosition.y * std::abs(frustum.z - frustum.w)) /
						(static_cast<float>(framebufferSize.x) / aspectRatio),
					guiPosition.z);

				auto guiScale = guiComponent->scale;

				transformComponent->scale = Vector3(
					(guiScale.x * std::abs(frustum.x - frustum.y)) /
						(static_cast<float>(framebufferSize.x) / aspectRatio),
					(guiScale.y * std::abs(frustum.z - frustum.w)) /
						static_cast<float>(framebufferSize.y),
					guiScale.z);
			}
			else
			{
				transformComponent->position = guiPosition;
				transformComponent->scale = guiComponent->scale;
			}

			transformComponent->rotation = guiComponent->rotation;
			transformComponent->parent = guiComponent->parent;
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
