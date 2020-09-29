#pragma once
#include "Injector/System.hpp"
#include "Injector/Graphics/Window.hpp"

namespace Injector
{
	class SimSkySystem : public System
	{
	 protected:
		std::shared_ptr<Window> window;

	 public:
		explicit SimSkySystem(
			const std::shared_ptr<Window>& window);

		void update() override;
	};
}
