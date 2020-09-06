#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Engine.hpp"

#include <stdexcept>

namespace Injector::Graphics
{
	RenderSystem::~RenderSystem()
	{}

	size_t RenderSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}
	bool RenderSystem::addCamera(const shared_ptr<Entity>& entity) noexcept
	{
		return cameras.emplace(entity).second;
	}
	bool RenderSystem::removeCamera(const shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	void RenderSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
}
