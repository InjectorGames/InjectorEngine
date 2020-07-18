#pragma once
#include <injector/defines.hpp>

#include <map>
#include <typeindex>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	class Manager;

	struct Entity final
	{
		size_t id;
		Manager& manager;

		Entity(size_t id, Manager& manager);

		bool destroy() noexcept;
		bool isValid() const noexcept;

		size_t getComponentCount() const noexcept;
		bool getComponentCount(size_t& count) const noexcept;
		bool destroyComponents() noexcept;

		template<class T, typename ...Args>
		T* createComponent(Args... args)
		{
			return manager.createComponent<T>(id, args...);
		}
		template<class T, class ...Args>
		bool createComponent(T*& component, Args... args) noexcept
		{
			return manager.createComponent<T>(id, component, args...);
		}
		template<class T>
		bool destroyComponent() noexcept
		{
			return manager.destroyComponent<T>(id);
		}

		template<class T>
		T* getComponent()
		{
			return manager.getComponent<T>(id);
		}
		template<class T>
		const T* getComponent() const
		{
			return manager.getComponent<T>(id);
		}
		template<class T>
		bool getComponent(T*& component) noexcept
		{
			return manager.getComponent<T>(id, component);
		}
		template<class T>
		bool getComponent(const T*& component) const noexcept
		{
			return manager.getComponent<T>(id, component);
		}

		bool operator==(const Entity& other);
		bool operator!=(const Entity& other);
	};
}
