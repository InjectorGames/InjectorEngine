#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Exception/Exception.hpp"

#include <map>
#include <typeindex>

namespace Injector
{
	// Entity Component System entity structure
	struct EcsEntity final
	{
	 private:
		// Component map
		std::map<std::type_index, EcsComponent*> components;
	 public:
		// Creates a new ECS entity
		EcsEntity() noexcept;
		// Deleted ECS entity copy constructor
		EcsEntity(const EcsEntity& entity) = default;
		// Deleted ECS entity move constructor
		EcsEntity(EcsEntity&& entity) = default;
		// Destroys ECS entity and all components
		~EcsEntity();

		// Destroys all ECS entity components
		void destroyComponents() noexcept;
		// Returns ECS entity component count
		size_t getComponentCount() const noexcept;

		// Returns a new created and added to the entity component
		// with specified arguments
		template<class T, class ...Args>
		T* createComponent(Args... args)
		{
			auto component = new T(args...);

			if (!components.emplace(typeid(T), component).second)
			{
				delete component;

				throw Exception(
					std::string(typeid(EcsEntity).name()),
					std::string(__func__),
					std::to_string(__LINE__),
					"Failed to add component");
			}

			return component;
		}
		// Returns true if component has been created
		// and added to the entity
		template<class T, class ...Args>
		bool createComponent(T*& _component, Args... args) noexcept
		{
			auto component = new T(args...);

			if (!components.emplace(typeid(T), component).second)
			{
				delete component;
				return false;
			}

			_component = component;
			return true;
		}
		// Returns true if component has been destroyed
		// and removed from the entity
		template<class T>
		bool destroyComponent() noexcept
		{
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			delete iterator->second;
			components.erase(iterator);
			return true;
		}
		// Returns true if entity contains specified component
		template<class T>
		bool containsComponent() noexcept
		{
			return components.find(typeid(T)) != components.end();
		}

		// Returns specified entity component
		template<class T>
		T* getComponent()
		{
			return static_cast<T*>(components.at(typeid(T)));
		}
		// Returns specified constant entity component
		template<class T>
		const T* getComponent() const
		{
			return static_cast<const T*>(components.at(typeid(T)));
		}
		// Returns true and specified component if entity contains it
		template<class T>
		bool getComponent(T*& component) noexcept
		{
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			component = static_cast<T*>(iterator->second);
			return true;
		}
		// Returns true and specified constant entity component if contains
		template<class T>
		bool getComponent(const T*& component) const noexcept
		{
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			component = static_cast<const T*>(iterator->second);
			return true;
		}
	};
}
