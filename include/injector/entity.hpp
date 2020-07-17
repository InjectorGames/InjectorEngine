#pragma once
#include <injector/component.hpp>

#include <map>
#include <typeindex>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	class Manager;

	class Entity final
	{
	protected:
		size_t id;
		Manager& manager;
	public:
		Entity(size_t id, Manager& manager);

		inline size_t getID() const noexcept;
		inline Manager& getManager() const noexcept;

		inline bool isValid() const noexcept;
		inline size_t getComponentCount() const noexcept;
		inline bool removeComponents() noexcept;

		template<class T>
		inline T* addComponent()
		{
			auto& components = manager.entities.at(id);
			auto component = new T();

			if (!components.emplace(typeid(T), component).second)
			{
				delete component;
				throw std::runtime_error("Failed to add entity component");
			}

			return component;
		}
		template<class T>
		inline bool addComponent(T* component) noexcept
		{
			auto& entities = manager.entities;
			auto iterator = entities.find(id);

			if (iterator == entities.end())
				return false;

			component = new T();

			if (!iterator->second.emplace(typeid(T), component).second)
			{
				delete component;
				return false;
			}

			return true;
		}

		template<class T>
		inline void removeComponent()
		{
			auto& components = manager.entities.at(id);
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				throw std::runtime_error("Failed to remove entity component");

			delete iterator->second;
			components.erase(iterator);
		}
		template<class T>
		inline bool removeComponent() noexcept
		{
			auto& entities = manager.entities;
			auto iterator = entities.find(id);
			
			if (iterator == entities.end())
				return false;

			auto& components = iterator->second;
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			delete iterator->second;
			components.erase(iterator);
			return true;
		}

		template<class T>
		inline T* getComponent()
		{
			auto& components = manager.entities.at(id);
			return components.at(typeid(T));
		}
		template<class T>
		inline const T* getComponent() const
		{
			auto& components = manager.entities.at(id);
			return components.at(typeid(T));
		}
		template<class T>
		inline bool getComponent(T* component) noexcept
		{
			auto& entities = manager.entities;
			auto iterator = entities.find(id);

			if (iterator == entities.end())
				return false;

			auto& components = iterator->second;
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			component = iterator->second;
			return true;
		}
		template<class T>
		inline bool getComponent(const T* component) const noexcept
		{
			auto& entities = manager.entities;
			auto iterator = entities.find(id);

			if (iterator == entities.end())
				return false;

			auto& components = iterator->second;
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			component = iterator->second;
			return true;
		}

		template<class T1, class T2>
		inline bool addComponents() noexcept
		{
			auto& entities = manager.entities;
			auto iterator = entities.find(id);

			if (iterator == entities.end())
				return false;

			auto& components = iterator->second;
			auto component = new T1();

			if (!components.emplace(component).second)
			{
				delete component;
				return false;
			}

			auto component = new T2();

			if (!components.emplace(component).second)
			{
				delete component;
				return false;
			}

			return true;
		}
	};
}
