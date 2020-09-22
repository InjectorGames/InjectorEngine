#include "Injector/Graphics/GuiSystem.hpp"

namespace Injector
{
	GuiSystem::GuiSystem() :
		guis()
	{
	}
	GuiSystem::~GuiSystem()
	{
	}

	size_t GuiSystem::getGuiCount() const noexcept
	{
		return guis.size();
	}

	void GuiSystem::update()
	{

	}

	bool GuiSystem::addGui(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return guis.emplace(entity).second;
	}
	bool GuiSystem::removeGui(
		const std::shared_ptr<Entity>& entity) noexcept
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
