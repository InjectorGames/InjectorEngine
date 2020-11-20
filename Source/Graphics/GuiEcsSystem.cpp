#include "Injector/Graphics/GuiEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/ImguiDefines.hpp"

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

		auto image = window->createImage(
			GpuImageFormat::R8G8B8A8UNORM,
			SizeVector2(
				width,
				height),
			false,
			pixels);
		auto vertexShader = window->createShader(
			GpuShaderStage::Vertex,
			window->readShaderData(
				"Resources/Shaders/Gui.vert"));
		auto fragmentShader = window->createShader(
			GpuShaderStage::Fragment,
			window->readShaderData(
				"Resources/Shaders/Gui.frag"));
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
			0,
			nullptr,
			nullptr);

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

		auto drawData = ImGui::GetDrawData();
		CameraEcsComponent* cameraComponent;
		RenderEcsComponent* renderComponent;

		if(drawData->CmdListsCount == 0 ||
			!cameraEntity->getComponent(cameraComponent) ||
			!guiEntity->getComponent(renderComponent) ||
			!renderComponent->mesh)
		{
			return;
		}

		cameraComponent->frustum = FloatVector4(
			drawData->DisplayPos.x,
			drawData->DisplayPos.x + drawData->DisplaySize.x,
			drawData->DisplayPos.y + drawData->DisplaySize.y,
			drawData->DisplayPos.y);
		cameraComponent->clipPlane = FloatVector2(
			1.0f,
			-1.0f);

		auto vertexBuffer = window->createBuffer(
			drawData->TotalVtxCount * sizeof(ImDrawVert),
			GpuBufferType::Vertex,
			true,
			nullptr);
		auto vertexBufferMap = reinterpret_cast<ImDrawVert*>(
			vertexBuffer->map(GpuBufferAccess::WriteOnly));
		auto vertexMapIndex = 0;

		auto drawCommands = drawData->CmdLists;

		for (int i = 0; i < drawData->CmdListsCount; i++)
		{
			auto drawCommand = drawCommands[i];
			memcpy(
				vertexBufferMap + vertexMapIndex,
				drawCommand->VtxBuffer.Data,
				drawCommand->VtxBuffer.Size * sizeof(ImDrawVert));
			vertexMapIndex += drawCommand->VtxBuffer.Size;
		}

		vertexBuffer->unmap();

		auto indexBuffer = window->createBuffer(
			drawData->TotalIdxCount * sizeof(ImDrawIdx),
			GpuBufferType::Index,
			true,
			nullptr);
		auto indexBufferMap = reinterpret_cast<ImDrawIdx*>(
			indexBuffer->map(GpuBufferAccess::WriteOnly));
		auto indexMapIndex = 0;

		for (int i = 0; i < drawData->CmdListsCount; i++)
		{
			auto drawCommand = drawCommands[i];
			memcpy(
				indexBufferMap + indexMapIndex,
				drawCommand->IdxBuffer.Data,
				drawCommand->IdxBuffer.Size * sizeof(ImDrawIdx));
			indexMapIndex += drawCommand->IdxBuffer.Size;
		}

		indexBuffer->unmap();

		auto mesh = renderComponent->mesh;
		mesh->indexCount = drawData->TotalIdxCount;
		mesh->setVertexBuffer(vertexBuffer);
		mesh->setIndexBuffer(indexBuffer);

		// TODO: fill buffers
		// implement vma defragmentation
		// vma autoselect best memoty allocation way in the buffer and image
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
