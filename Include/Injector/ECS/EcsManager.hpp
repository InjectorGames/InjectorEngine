#pragma once
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/ECS/EcsSystem.hpp"

#include <set>
#include <vector>
#include <memory>

namespace Injector
{
	// Entity Component System manager
	class EcsManager
	{
	 protected:
		// Is manager still active
		bool active;

		// Manager entity container
		std::set<std::shared_ptr<EcsEntity>> entities;
		// Manager system container
		std::vector<std::shared_ptr<EcsSystem>> systems;
	 public:
		// Creates a new manager
		explicit EcsManager(
			bool active = true) noexcept;
		// Deleted manager copy constructor
		EcsManager(const EcsManager& manager) = delete;
		// Deleted manager move constructor
		EcsManager(EcsManager&& manager) = delete;
		// Destroys all entities, systems and manager
		virtual ~EcsManager() = default;

		// Executes on each update cycle
		virtual void update();

		// Returns true if manager is still active
		bool isActive() const noexcept;
		// Returns manager entity count
		size_t getEntityCount() const noexcept;
		// Returns manager system count
		size_t getSystemCount() const noexcept;

		// Returns a new created and added to the manager entity
		std::shared_ptr<EcsEntity> createEntity();

		// Returns a new created and added to the manager system
		template<class T, class ...Args>
		std::shared_ptr<T> createSystem(Args... args) noexcept
		{
			auto system = std::make_shared<T>(args...);
			systems.push_back(system);
			return system;
		}

		// Returns true if specified entity has been removed from system
		bool removeEntity(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		// Returns true if specified system has been removed from system
		bool removeSystem(
			const std::shared_ptr<EcsSystem>& system) noexcept;

		// Returns true if manager contains specified entity
		bool containsEntity(
			const std::shared_ptr<EcsEntity>& entity) const noexcept;
		// Returns true if manager contains specified system
		bool containsSystem(
			const std::shared_ptr<EcsSystem>& system) const noexcept;

		// Removes all manager entities
		void removeEntities() noexcept;
		// Removes all manager systems
		void removeSystems() noexcept;
	};
}