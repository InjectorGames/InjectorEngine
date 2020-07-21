#pragma once
#include <injector/entity.hpp>
#include <injector/system.hpp>

#include <set>
#include <vector>

namespace INJECTOR_NAMESPACE
{
	class Manager
	{
	protected:
		std::set<EntityHandle> entities;
		std::vector<std::shared_ptr<System>> systems;
	public:
		Manager();
		virtual ~Manager();

		virtual void update();

		EntityHandle createEntity();
		bool createEntity(EntityHandle& entity) noexcept;
		bool addEntity(const EntityHandle& entity) noexcept;
		bool removeEntity(const EntityHandle& entity) noexcept;
		bool containsEntity(const EntityHandle& entity) const noexcept;
		void removeEntities() noexcept;
		size_t getEntityCount() const noexcept;

		bool addSystem(const SystemHandle& system) noexcept;
		bool removeSystem(const SystemHandle& system) noexcept;
		bool containsSystem(const SystemHandle& system) noexcept;
		void removeSystems() noexcept;
		size_t getSystemCount() const noexcept;

		template<class T, class ...Args>
		std::shared_ptr<T> createSystem(Args... args) noexcept
		{
			auto system = std::make_shared<T>(args...);
			systems.push_back(system);
			return system;
		}
	};

	using ManagerHandle = std::shared_ptr<Manager>;
}