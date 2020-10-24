#include "Injector/Graphics/GUI/EditorGuiHandler.hpp"

namespace Injector
{
	void EditorGuiHandler::create(
		const std::shared_ptr<GpuWindow>& window,
		const std::shared_ptr<GuiSystem>& guiSystem,
		const std::shared_ptr<TransformEcsSystem>& transformSystem,
		std::set<std::shared_ptr<EcsEntity>>& renders)
	{
		auto colorVertexShader = window->createShader(
			GpuShaderStage::Vertex,
			window->readShaderData(
				"Resources/Shaders/Color.vert"));
		auto colorFragmentShader = window->createShader(
			GpuShaderStage::Fragment,
			window->readShaderData(
				"Resources/Shaders/Color.frag"));
		auto colorPipeline = window->createColorPipeline(
			GpuDrawMode::TriangleList,
			colorVertexShader,
			colorFragmentShader,
			Vector4(
				63 / 255.0f,
				63 / 255.0f,
				63 / 255.0f,
				255 / 255.0f));

		auto squareMesh = window->createMesh(
			ModelData::square.getVertex(),
			false,
			ModelData::square.indices,
			false);

		auto bar = window->createEntity();
		bar->createComponent<TransformEcsComponent>();
		bar->createComponent<GuiEcsComponent>(
			Vector3::zero,
			Quaternion(Vector3::zero),
			Vector3(
				1.5f,
				0.25f,
				1.0f),
			GuiAnchorType::Left);
		bar->createComponent<RenderEcsComponent>(
			colorPipeline,
			squareMesh);
		guiSystem->addGui(bar);
		transformSystem->addTransform(bar);
		renders.emplace(bar);
	}
}
