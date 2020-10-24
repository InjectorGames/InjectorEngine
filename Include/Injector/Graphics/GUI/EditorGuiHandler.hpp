#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/GUI/GuiSystem.hpp"
#include "Injector/Mathematics/TransformEcsSystem.hpp"


namespace Injector
{
	class EditorGuiHandler
	{
	 public:
		static void create(
			const std::shared_ptr<GpuWindow>& window,
			const std::shared_ptr<GuiSystem>& guiSystem,
			const std::shared_ptr<TransformEcsSystem>& transformSystem,
			std::set<std::shared_ptr<EcsEntity>>& renders);
	};
}
