#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Engine.hpp"

#include <stdexcept>

namespace Injector
{
	RenderEcsSystem::RenderEcsSystem() noexcept :
		cameras(),
		guis()
	{
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		RenderEcsSystem::getCameras() const noexcept
	{
		return cameras;
	}
	const std::set<std::shared_ptr<EcsEntity>>&
	RenderEcsSystem::getGuis() const noexcept
	{
		return guis;
	}

	bool RenderEcsSystem::addCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return cameras.emplace(entity).second;
	}
	bool RenderEcsSystem::removeCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}

	bool RenderEcsSystem::addGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return guis.emplace(entity).second;
	}
	bool RenderEcsSystem::removeGui(
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

	void RenderEcsSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
	void RenderEcsSystem::removeGuis() noexcept
	{
		guis.clear();
	}
}
