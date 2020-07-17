#pragma once
#include <injector/entity.hpp>
#include <injector/system.hpp>

namespace INJECTOR_NAMESPACE
{
	class Manager
	{
	protected:
		size_t id;
		bool active;

		bool initialized;
		size_t freeEntityID;

		std::map<std::type_index, System*> systems;
		std::map<size_t, std::map<std::type_index, Component*>> entities;

		friend class Entity;
	public:
		Manager(size_t id, bool active = true);

		inline size_t getID() const noexcept;
		inline bool getActive() const noexcept;

		inline bool getInitialized() const noexcept;
		inline size_t getFreeEntityID() const noexcept;

		inline void initialize();
		inline void terminate();

		inline Entity createEntity();
	};
}