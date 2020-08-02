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
		std::vector<System*> systems;
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

		template<class T, class ...Args>
		T* createSystem(Args... args) noexcept
		{
			auto system = new T(args...);
			systems.push_back(system);
			return system;
		}

		bool removeSystem(const System* system) noexcept;
		bool containsSystem(const System* system) noexcept;
		void removeSystems() noexcept;
		size_t getSystemCount() const noexcept;
	};

	using ManagerHandle = std::shared_ptr<Manager>;
}