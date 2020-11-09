#include "Injector/Graphics/GUI/EditorGuiHandler.hpp"
#include "Injector/Mathematics/Color.hpp"

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
		auto darkColorPipeline = window->createColorPipeline(
			GpuDrawMode::TriangleList,
			colorVertexShader,
			colorFragmentShader,
			Color::toVector(
				47,53,66,255));
		auto greyColorPipeline = window->createColorPipeline(
			GpuDrawMode::TriangleList,
			colorVertexShader,
			colorFragmentShader,
			Color::toVector(
				87,96,111,255));

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
			Quaternion::zero,
			Vector3::one,
			GuiAnchorType::Center,
			false,
			nullptr,
			nullptr);
		guiSystem->addGui(editorWindow);
		transformSystem->addTransform(editorWindow);

		auto bar = window->createEntity();
		bar->createComponent<TransformEcsComponent>();
		bar->createComponent<GuiEcsComponent>(
			Vector3(
				0.0f,
				65.0f,
				0.0f),
			Quaternion::zero,
			Vector3(
				300.0f,
				30.0f,
				1.0f),
			GuiAnchorType::Center,
			true,
			editorWindow);
		bar->createComponent<RenderEcsComponent>(
			greyColorPipeline,
			squareMesh);
		guiSystem->addGui(bar);
		transformSystem->addTransform(bar);
		renders.emplace(bar);

		auto panel = window->createEntity();
		panel->createComponent<TransformEcsComponent>();
		panel->createComponent<GuiEcsComponent>(
			Vector3::zero,
			Quaternion::zero,
			Vector3(
				300.0f,
				100.0f,
				1.0f),
			GuiAnchorType::Center,
			true,
			editorWindow);
		panel->createComponent<RenderEcsComponent>(
			darkColorPipeline,
			squareMesh);
		guiSystem->addGui(panel);
		transformSystem->addTransform(panel);
		renders.emplace(panel);
	}
}
