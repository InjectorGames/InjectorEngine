#include "Injector/Graphics/GuiEcsSystem.hpp"
#include "Injector/Exception/Exception.hpp"

#include "examples/imgui_impl_glfw.h"

namespace Injector
{
	GuiEcsSystem::GuiEcsSystem() noexcept :
		guis()
	{
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		GuiEcsSystem::getGuis() const noexcept
	{
		return guis;
	}

	void GuiEcsSystem::initialize(
		const std::shared_ptr<GpuWindow>& window,
		const std::shared_ptr<RenderEcsSystem>& _renderSystem)
	{

		// TODO:
		// 1. Get systems in arguments

		// TODO:
		// 1. Create GUI shader with texture
		// 2. Create render buffer and entity


		renderSystem = _renderSystem;

		/*auto pipeline = window.crea
		auto render = EcsEntity::create();
		render->createComponent<RenderEcsComponent>(
			BoundingBox3::one
			);*/
	}

	void GuiEcsSystem::onUpdate()
	{
		if(!renderSystem || !renderComponent)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Not initialized");
		}

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto& gui : guis)
		{
			GuiEcsComponent* guiComponent;

			if(!gui->getComponent(guiComponent))
				continue;

			if(guiComponent->handler)
				guiComponent->handler->onUpdate();
		}

		ImGui::Render();

		// TODO: fill buffers
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
