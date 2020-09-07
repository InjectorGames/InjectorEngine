#pragma once
#include "Injector/Entity.hpp"
#include "Injector/System.hpp"

#include <set>
#include <vector>
#include <memory>

namespace Injector
{
	class Manager
	{
	protected:
		bool active;
		std::set<std::shared_ptr<Entity>> entities;
		std::vector<std::shared_ptr<System>> systems;
	public:
		Manager(bool active = true);
		virtual ~Manager();

		virtual void update();

		bool isActive() const noexcept;
		size_t getEntityCount() const noexcept;
		size_t getSystemCount() const noexcept;

		std::shared_ptr<Entity> createEntity();
		bool addEntity(const std::shared_ptr<Entity>& entity) noexcept;

		template<class T, class ...Args>
		std::shared_ptr<T> createSystem(Args... args) noexcept
		{
			auto system = std::make_shared<T>(args...);
			systems.push_back(system);
			return system;
		}
		
		bool removeEntity(const std::shared_ptr<Entity>& entity) noexcept;
		bool destroySystem(const std::shared_ptr<System>& system) noexcept;

		bool containsEntity(const std::shared_ptr<Entity>& entity) const noexcept;
		bool containsSystem(const std::shared_ptr<System>& system) noexcept;

		void removeEntities() noexcept;
		void destroySystems() noexcept;
	};
}