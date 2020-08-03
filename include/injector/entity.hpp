#pragma once
#include <injector/system.hpp>
#include <injector/component.hpp>

#include <map>
#include <memory>
#include <typeindex>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	class Entity final
	{
	private:
		std::map<std::type_index, Component*> components;
	public:
		Entity();
		~Entity();

		void Entity::destroyComponents() noexcept;
		size_t getComponentCount() const noexcept;

		template<class T, class ...Args>
		T* createComponent(Args... args)
		{
			auto component = new T(args...);

			if (!components.emplace(typeid(T), component).second)
			{
				delete component;
				throw std::runtime_error("Failed to add entity component");
			}

			return component;
		}
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
		template<class T>
		bool containsComponent() noexcept
		{
			return components.find(typeid(T)) != components.end();
		}

		template<class T>
		T* getComponent()
		{
			return static_cast<T*>(components.at(typeid(T)));
		}
		template<class T>
		const T* getComponent() const
		{
			return static_cast<const T*>(components.at(typeid(T)));
		}
		template<class T>
		bool getComponent(T*& component) noexcept
		{
			auto iterator = components.find(typeid(T));

			if (iterator == components.end())
				return false;

			component = static_cast<T*>(iterator->second);
			return true;
		}
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

	using EntityHandle = std::shared_ptr<Entity>;
}
