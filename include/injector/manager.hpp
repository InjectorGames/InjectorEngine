#pragma once
#include <injector/entity.hpp>
#include <injector/system.hpp>

namespace INJECTOR_NAMESPACE
{
	class Manager
	{
	public:
		using Components = std::map<std::type_index, void*>;
	protected:
		size_t id;
		bool active;

		bool initialized;
		size_t freeEntityID;

		std::map<std::type_index, System*> systems;
		std::map<size_t, Components> entities;

		friend class Entity;
	public:
		Manager(size_t id, bool active = true);
		virtual ~Manager();

		size_t getID() const noexcept;
		bool getActive() const noexcept;

		bool getInitialized() const noexcept;
		size_t getFreeEntityID() const noexcept;

		void initialize();
		void terminate();

		Entity createEntity();
		size_t getEntityCount() const noexcept;
		bool isContainsEntity(size_t id) const noexcept;

		bool removeEntity(size_t id) noexcept;
		bool removeEntities() noexcept;
	};
}