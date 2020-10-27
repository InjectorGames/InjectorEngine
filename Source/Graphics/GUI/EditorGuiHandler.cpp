#include "Injector/Graphics/GUI/EditorGuiHandler.hpp"

namespace Injector
{
	void EditorGuiHandler::create(
		const std::shared_ptr<GpuWindow>& window,
		const std::shared_ptr<GuiEcsSystem>& guiSystem,
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

		// TODO: create editor interface
		// Also process anchor parenting and other stuff

		auto editorWindow = window->createEntity();
		editorWindow->createComponent<TransformEcsComponent>();
		editorWindow->createComponent<GuiEcsComponent>(
			Vector3::zero,
			Quaternion(Vector3::zero),
			Vector3(
				150.0f,
				25.0f,
				1.0f),
			GuiAnchorType::Center,
			true);

		auto bar = window->createEntity();
		bar->createComponent<TransformEcsComponent>();
		bar->createComponent<GuiEcsComponent>(
			Vector3::zero,
			Quaternion(Vector3::zero),
			Vector3(
				150.0f,
				25.0f,
				1.0f),
			GuiAnchorType::Center,
			true);
		bar->createComponent<RenderEcsComponent>(
			colorPipeline,
			squareMesh);
		guiSystem->addGui(bar);
		transformSystem->addTransform(bar);
		renders.emplace(bar);
	}
}
