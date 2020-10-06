#pragma once
#include "Injector/ECS/Entity.hpp"
#include "Injector/ECS/System.hpp"

#include <set>
#include <vector>
#include <memory>

namespace Injector
{
	class Manager
	{
	 protected:
		// Is manager still active
		bool active;

		// Manager entity container
		std::set<std::shared_ptr<Entity>> entities;
		// Manager system container
		std::vector<std::shared_ptr<System>> systems;
	 public:
		// Creates a new manager
		explicit Manager(
			bool active = true) noexcept;
		// Deleted manager copy constructor
		Manager(const Manager& manager) = delete;
		// Deleted manager move constructor
		Manager(Manager&& manager) = delete;
		// Destroys all entities, systems and manager
		virtual ~Manager() = default;

		// Executes on each update cycle
		virtual void update();

		// Returns true if manager is still active
		bool isActive() const noexcept;
		// Returns manager entity count
		size_t getEntityCount() const noexcept;
		// Returns manager system count
		size_t getSystemCount() const noexcept;

		// Returns a new created and added to the manager entity
		std::shared_ptr<Entity> createEntity();

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
			const std::shared_ptr<Entity>& entity) noexcept;
		// Returns true if specified system has been removed from system
		bool removeSystem(
			const std::shared_ptr<System>& system) noexcept;

		// Returns true if manager contains specified entity
		bool containsEntity(
			const std::shared_ptr<Entity>& entity) const noexcept;
		// Returns true if manager contains specified system
		bool containsSystem(
			const std::shared_ptr<System>& system) noexcept;

		// Removes all manager entities
		void removeEntities() noexcept;
		// Removes all manager systems
		void removeSystems() noexcept;
	};
}