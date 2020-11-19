#include "Injector/Graphics/GuiEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"

#include "examples/imgui_impl_glfw.h"

namespace Injector
{
	GuiEcsSystem::GuiEcsSystem(
		const std::shared_ptr<GpuWindow>& _window) :
		window(_window),
		guis()
	{
		if(!_window)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"window");
		}
	}
	GuiEcsSystem::~GuiEcsSystem()
	{
		window->removeEntity(cameraEntity);
		window->removeEntity(guiEntity);
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		GuiEcsSystem::getGuis() const noexcept
	{
		return guis;
	}

	void GuiEcsSystem::initialize(
		const std::shared_ptr<TransformEcsSystem>& _transformSystem,
		const std::shared_ptr<CameraEcsSystem>& _cameraSystem,
		const std::shared_ptr<RenderEcsSystem>& _renderSystem)
	{
		if(cameraEntity || guiEntity)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already initialized");
		}

		ImGuiIO& io = ImGui::GetIO();

		unsigned char* pixels;
		int width, height;

		io.Fonts->GetTexDataAsRGBA32(
			&pixels,
			&width,
			&height);

		auto pixelDataSize =
			sizeof(unsigned char) * width * height * 4;
		auto pixelData = std::vector<uint8_t>(
			pixelDataSize);

		memcpy(
			pixelData.data(),
			pixels,
			pixelDataSize);

		auto imageData = std::make_shared<ImageData>(
			SizeVector3(
				width,
				height,
				1),
				4,
				false,
			pixelData);
		auto image = window->createImage(
			GpuImageFormat::RGBA8,
			SizeVector2(
				width,
				height),
			false,
			imageData);
		auto vertexShader = window->createShader(
			GpuShaderStage::Vertex,
			window->readShaderData("Resources/Shaders/Gui.vert"));
		auto fragmentShader = window->createShader(
			GpuShaderStage::Fragment,
			window->readShaderData("Resources/Shaders/Gui.frag"));
		auto pipeline = window->createGuiPipeline(
			GpuDrawMode::TriangleList,
			GpuImageFilter::Linear,
			GpuImageFilter::Linear,
			GpuImageFilter::Linear,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			vertexShader,
			fragmentShader,
			image,
			FloatVector2(1.0f),
			FloatVector2(0.0f));
		auto mesh = window->createMesh(
			std::vector<float>(),
			true,
			std::vector<uint32_t>(),
			true);

		cameraEntity = EcsEntity::create();
		auto cameraComponent = cameraEntity->createComponent<CameraEcsComponent>(
			1,
			CameraType::Orthographic);
		cameraEntity->createComponent<TransformEcsComponent>();
		_cameraSystem->addCamera(cameraEntity);
		_transformSystem->addTransform(cameraEntity);

		guiEntity = EcsEntity::create();
		guiEntity->createComponent<RenderEcsComponent>(
			BoundingBox3::one,
			pipeline,
			mesh);
		guiEntity->createComponent<TransformEcsComponent>();
		cameraComponent->renders.emplace(guiEntity);
		_transformSystem->addTransform(guiEntity);
	}

	void GuiEcsSystem::onUpdate()
	{
		if(!cameraEntity || !guiEntity)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Not initialized");
		}

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto& gui : guis)
		{
			GuiEcsComponent* guiComponent;

			if(!gui->getComponent(guiComponent))
				continue;

			if(guiComponent->handler)
				guiComponent->handler->onUpdate();
		}

		ImGui::Render();

		// TODO: fill buffers


	}

	bool GuiEcsSystem::removeEntity(
		const std::shared_ptr<EcsEntity>& entity)
	{
		return removeGui(entity);
	}

	bool GuiEcsSystem::addGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return guis.emplace(entity).second;
	}
	bool GuiEcsSystem::removeGui(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = guis.find(entity);

		if (iterator == guis.end())
			return false;

		guis.erase(iterator);
		return true;
	}

	void GuiEcsSystem::removeGuis() noexcept
	{
		guis.clear();
	}
}
