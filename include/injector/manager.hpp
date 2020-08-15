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
		bool active;
		std::set<EntityHandle> entities;
		std::vector<SystemHandle> systems;
	public:
		Manager(bool active = true);
		virtual ~Manager();

		virtual void update();

		bool isActive() const noexcept;
		size_t getEntityCount() const noexcept;
		size_t getSystemCount() const noexcept;

		EntityHandle createEntity();
		bool addEntity(const EntityHandle& entity) noexcept;

		template<class T, class ...Args>
		std::shared_ptr<T> createSystem(Args... args) noexcept
		{
			auto system = std::make_shared<T>(args...);
			systems.push_back(system);
			return system;
		}
		
		bool removeEntity(const EntityHandle& entity) noexcept;
		bool destroySystem(const SystemHandle& system) noexcept;

		bool containsEntity(const EntityHandle& entity) const noexcept;
		bool containsSystem(const SystemHandle& system) noexcept;

		void removeEntities() noexcept;
		void destroySystems() noexcept;
	};

	using ManagerHandle = std::shared_ptr<Manager>;
}