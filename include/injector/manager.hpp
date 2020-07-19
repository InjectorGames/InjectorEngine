#pragma once
#include <injector/system.hpp>

#include <map>
#include <typeindex>

namespace INJECTOR_NAMESPACE
{
	class Manager
	{
	public:
		using Components = std::map<std::type_index, void*>;
	protected:
		size_t id;
		size_t freeEntityID;

		std::map<std::type_index, System*> systems;
		std::map<size_t, Components> entities;

		friend class Entity;
	public:
		Manager(size_t id);
		virtual ~Manager();

		virtual void update();

		size_t getID() const noexcept;
		size_t getFreeEntityID() const noexcept;
		
		size_t createEntity();
		bool destroyEntity(size_t id) noexcept;
		void destroyEntities() noexcept;
		size_t getEntityCount() const noexcept;
		bool containsEntity(size_t id) const noexcept;

		size_t getComponentCount(size_t id) const;
		bool getComponentCount(size_t id, size_t& count) const noexcept;
		bool destroyComponents(size_t id) noexcept;

		template<class T, typename ...Args>
		T* createComponent(size_t id, Args... args)
		{
			if (id == 0)
				throw std::runtime_error("Entity id is null");

			auto& components = entities.at(id);
			auto component = new T(args...);

			if (!components.emplace(typeid(T), component).second)
			{
				delete component;
				throw std::runtime_error("Failed to add entity component");
			}

			return component;
		}
		template<class T, class ...Args>
		bool createComponent(size_t id, T*& component, Args... args) noexcept
		{
			if (id == 0)
				return false;

			auto iterator = entities.find(id);

			if (iterator == entities.end())
				return false;

			component = new T(args...);

			if (!iterator->second.emplace(typeid(T), component).second)
			{
				delete component;
				return false;
			}

			return true;
		}
		template<class T>
		bool destroyComponent(size_t id) noexcept
		{
			if (id == 0)
				return false;

			auto entityIterator = entities.find(id);

			if (entityIterator == entities.end())
				return false;

			auto& components = entityIterator->second;
			auto componentIterator = components.find(typeid(T));

			if (componentIterator == components.end())
				return false;

			delete componentIterator->second;
			components.erase(componentIterator);
			return true;
		}

		template<class T>
		T* getComponent(size_t id)
		{
			if (id == 0)
				throw std::runtime_error("Entity id is null");

			auto& components = entities.at(id);
			return static_cast<T*>(components.at(typeid(T)));
		}
		template<class T>
		const T* getComponent(size_t id) const
		{
			if (id == 0)
				throw std::runtime_error("Entity id is null");

			auto& components = entities.at(id);
			return static_cast<const T*>(components.at(typeid(T)));
		}
		template<class T>
		bool getComponent(size_t id, T*& component) noexcept
		{
			if (id == 0)
				return false;

			auto entityIterator = entities.find(id);

			if (entityIterator == entities.end())
				return false;

			auto& components = entityIterator->second;
			auto componentIterator = components.find(typeid(T));

			if (componentIterator == components.end())
				return false;

			component = static_cast<T*>(componentIterator->second);
			return true;
		}
		template<class T>
		bool getComponent(size_t id, const T*& component) const noexcept
		{
			if (id == 0)
				return false;

			auto entityIterator = entities.find(id);

			if (entityIterator == entities.end())
				return false;

			auto& components = entityIterator->second;
			auto componentIterator = components.find(typeid(T));

			if (componentIterator == components.end())
				return false;

			component = static_cast<const T*>(componentIterator->second);
			return true;
		}

		size_t getSystemCount() const noexcept;
		void destroySystems() noexcept;

		template<class T>
		T* createSystem()
		{
			auto system = new T(*this);

			if (!systems.emplace(typeid(T), system).second)
			{
				delete system;
				throw std::exception("Failed to add manager system");
			}

			return system;
		}
		template<class T>
		bool createSystem(T*& system) noexcept
		{
			system = new T(*this);

			if (!systems.emplace(typeid(T), system).second)
			{
				delete system;
				return false;
			}

			return true;
		}

		template<class T>
		T* getSystem()
		{
			return dynamic_cast<T*>(systems.at(typeid(T)));
		}
		template<class T>
		const T* getSystem() const
		{
			return dynamic_cast<T*>(systems.at(typeid(T)));
		}
		template<class T>
		bool getSystem(T*& system) noexcept
		{
			auto iterator = systems.find(typeid(T));

			if (iterator == systems.end())
				return false;

			system = dynamic_cast<T*>(iterator->second);
			return true;
		}
		template<class T>
		bool getSystem(const T*& system) const noexcept
		{
			auto iterator = systems.find(typeid(T));

			if (iterator == systems.end())
				return false;

			system = dynamic_cast<T*>(iterator->second);
			return true;
		}

		bool operator==(const Manager& other);
		bool operator!=(const Manager& other);
		bool operator<(const Manager& other);
		bool operator>(const Manager& other);
		bool operator<=(const Manager& other);
		bool operator>=(const Manager& other);
	};
}