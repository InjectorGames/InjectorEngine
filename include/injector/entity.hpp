#pragma once
#include <injector/defines.hpp>

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

		size_t getID() const noexcept;
		Manager& getManager() const noexcept;

		bool isValid() const noexcept;

		size_t getComponentCount() const noexcept;
		bool removeComponents() noexcept;

		template<class T>
		T* addComponent()
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
		bool addComponent(T* component) noexcept
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
		void removeComponent()
		{
			auto& components = manager.entities.at(id);
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				throw std::runtime_error("Failed to remove entity component");

			delete iterator->second;
			components.erase(iterator);
		}
		template<class T>
		bool removeComponent() noexcept
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
		T* getComponent()
		{
			auto& components = manager.entities.at(id);
			return components.at(typeid(T));
		}
		template<class T>
		const T* getComponent() const
		{
			auto& components = manager.entities.at(id);
			return components.at(typeid(T));
		}
		template<class T>
		bool getComponent(T* component) noexcept
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
		bool getComponent(const T* component) const noexcept
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
		bool addComponents() noexcept
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
		template<class T1, class T2, class T3>
		bool addComponents() noexcept
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

			auto component = new T3();

			if (!components.emplace(component).second)
			{
				delete component;
				return false;
			}

			return true;
		}
		template<class T1, class T2, class T3, class T4>
		bool addComponents() noexcept
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

			auto component = new T3();

			if (!components.emplace(component).second)
			{
				delete component;
				return false;
			}

			auto component = new T4();

			if (!components.emplace(component).second)
			{
				delete component;
				return false;
			}

			return true;
		}
	};
}
