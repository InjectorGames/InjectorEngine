#include <injector/render_system.hpp>
#include <injector/engine.hpp>
#include <injector/graphics/gl_color_material.hpp>

namespace INJECTOR_NAMESPACE
{
	ShaderHandle RenderSystem::createShaderOpenGL(
		ShaderStage stage, const std::string& path)
	{
		return std::make_shared<GlShader>(false, stage, path);
	}
	ShaderHandle RenderSystem::createShaderOpenGLES(
		ShaderStage stage, const std::string& path)
	{
		return std::make_shared<GlShader>(true, stage, path);
	}
	ShaderHandle RenderSystem::createShaderVulkan(
		ShaderStage stage, const std::string& path)
	{
		throw std::runtime_error("Not implemented yet");
	}

	MaterialHandle RenderSystem::createColorOpenGL(
		const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto vertexShader = GlShader(false, ShaderStage::Vertex, vertexPath);
		auto fragmentShader = GlShader(false, ShaderStage::Fragment, fragmentPath);
		return std::make_shared<GlColorMaterial>(vertexShader, fragmentShader);
	}
	MaterialHandle RenderSystem::createColorOpenGLES(
		const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto vertexShader = GlShader(true, ShaderStage::Vertex, vertexPath);
		auto fragmentShader = GlShader(true, ShaderStage::Fragment, fragmentPath);
		return std::make_shared<GlColorMaterial>(vertexShader, fragmentShader);
	}
	MaterialHandle RenderSystem::createColorVulkan(
		const std::string& vertexPath, const std::string& fragmentPath)
	{
		throw std::runtime_error("Not implemented yet");
	}

	RenderSystem::RenderSystem(const EntityHandle& _window) :
		window(_window)
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		if (graphicsAPI == GraphicsAPI::OpenGL || graphicsAPI == GraphicsAPI::OpenGLES)
		{
			createShaderPointer = createShaderOpenGL;
			createColorPointer = createColorOpenGL;
		}
		else if (graphicsAPI == GraphicsAPI::Vulkan)
		{
			createShaderPointer = createShaderVulkan;
			createColorPointer = createColorVulkan;
		}
		else
		{
			throw std::runtime_error("Unknown graphics API");
		}
	}
	RenderSystem::~RenderSystem()
	{}

	void RenderSystem::update()
	{
		WindowComponent* windowComponent;

		if (window == nullptr || !window->getComponent<WindowComponent>(windowComponent))
			return;

		auto windowHandle = windowComponent->window;
		windowHandle->beginRender();

		std::multimap<int, EntityHandle> targetCameras;

		for (auto& camera : cameras)
		{
			CameraComponent* cameraComponent;

			if (camera->getComponent(cameraComponent) &&
				camera->containsComponent<TransformComponent>())
				targetCameras.emplace(cameraComponent->queue, camera);
		}

		for (auto& pair : targetCameras)
		{
			auto queue = pair.first;
			auto& camera = pair.second;

			auto cameraComponent = camera->getComponent<CameraComponent>();
			auto cameraTransformComponent = camera->getComponent<TransformComponent>();

			auto& clipPlane = cameraComponent->clipPlane;
			auto& projMatrix = cameraComponent->matrix;
			auto& viewMatrix = cameraTransformComponent->matrix;
			auto viewProjMatrix = projMatrix * viewMatrix;

			std::multimap<float, EntityHandle> targetRenders;

			for (auto& render : renders)
			{
				RenderComponent* renderComponent;
				TransformComponent* transformComponent;

				if (!render->getComponent(renderComponent) ||
					!render->getComponent(transformComponent) ||
					!renderComponent->render || renderComponent->queue != queue ||
					!renderComponent->material || !renderComponent->mesh)
					continue;

				auto order = 0.0f;

				if (renderComponent->ascending)
				{
					order = transformComponent->position.getDistance(
						-cameraTransformComponent->position) +
						clipPlane.y * renderComponent->offset;
					//targetRenders.emplace(glm::distance(-cameraTransform.position, glm::vec3(transformPosition)) + clipPlane.y * draw.offset, entity);
				}
				else
				{
					order = -transformComponent->position.getDistance(
						-cameraTransformComponent->position) +
						clipPlane.y * renderComponent->offset;
					//targetRenders.emplace(-glm::distance(-cameraTransform.position, glm::vec3(transformPosition)) + clipPlane.y * draw.offset, entity);
				}

				targetRenders.emplace(order, render);
			}

			for (auto& render : targetRenders)
			{
				auto renderComponent = render.second->getComponent<RenderComponent>();
				auto transformComponent = render.second->getComponent<TransformComponent>();

				auto& material = renderComponent->material;
				auto& mesh = renderComponent->mesh;
				auto& modelMatrix = transformComponent->matrix;
				auto mvpMatrix = viewProjMatrix * modelMatrix;

				material->use();

				material->setModelMatrix(modelMatrix);
				material->setViewMatrix(viewMatrix);
				material->setProjMatrix(projMatrix);
				material->setViewProjMatrix(viewProjMatrix);
				material->setMvpMatrix(mvpMatrix);

				mesh->draw();

				material->unuse();
				//drawCount++;
			}
		}

		windowHandle->endRender();
	}

	bool RenderSystem::addCamera(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<CameraComponent>() ||
			!entity->containsComponent<TransformComponent>())
			return false;

		return cameras.emplace(entity).second;
	}
	bool RenderSystem::removeCamera(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	void RenderSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
	size_t RenderSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}

	bool RenderSystem::addRender(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<RenderComponent>())
			return false;

		return renders.emplace(entity).second;
	}
	bool RenderSystem::removeRender(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = renders.find(entity);

		if (iterator == renders.end())
			return false;

		renders.erase(iterator);
		return true;
	}
	void RenderSystem::removeRenders() noexcept
	{
		renders.clear();
	}
	size_t RenderSystem::getRenderCount() const noexcept
	{
		return renders.size();
	}

	ShaderHandle RenderSystem::createShader(ShaderStage stage, const std::string& filePath)
	{
		return createShaderPointer(stage, filePath);
	}

	MaterialHandle RenderSystem::createColorMaterial(
		const std::string& vertexPath, const std::string& fragmentPath)
	{
		return createColorPointer(vertexPath, fragmentPath);
	}

	MeshHandle RenderSystem::createCubeMesh()
	{
		return nullptr;
	}
}
