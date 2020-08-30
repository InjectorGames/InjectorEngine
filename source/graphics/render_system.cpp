#include <injector/graphics/render_system.hpp>
#include <injector/engine.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	RenderSystem::~RenderSystem()
	{}

	size_t RenderSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}
	bool RenderSystem::addCamera(const EntityHandle& entity) noexcept
	{
		return cameras.emplace(entity).second;
	}
	bool RenderSystem::removeCamera(const EntityHandle& entity) noexcept
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
