#pragma once
#include "Injector/System.hpp"
#include "Injector/Entity.hpp"
#include "Injector/Graphics/GuiComponent.hpp"

#include <set>
#include <memory>

namespace Injector
{
	class GuiSystem : public System
	{
	 protected:
		std::set<std::shared_ptr<Entity>> guis;
	 public:
		GuiSystem();

		size_t getGuiCount() const noexcept;

		void update() override;

		bool addGui(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<Entity>& entity) noexcept;
		void removeGuis() noexcept;
	};
}
