#include <injector/render_system.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderSystem::RenderSystem(const EntityHandle& _window) :
		window(_window)
	{}
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
					!renderComponent->material)
					continue;

				auto& relative = transformComponent->parent;
				auto transformPosition = Vector4(transformComponent->position, 1.0f);

				while (relative)
				{
					TransformComponent* relativeTransform;

					if (!relative->getComponent(relativeTransform))
						break;

					transformPosition = relativeTransform->matrix * transformPosition;
					relative = relativeTransform->parent;
				}

				auto order = 0.0f;

				switch (renderComponent->order)
				{
				case RenderComponent::Order::Ascending:
					order = transformPosition.getVector3().getDistance(
						-cameraTransformComponent->position) + 
						clipPlane.y * renderComponent->offset;
					//targetRenders.emplace(glm::distance(-cameraTransform.position, glm::vec3(transformPosition)) + clipPlane.y * draw.offset, entity);
					break;
				case RenderComponent::Order::Descending:
					order = -transformPosition.getVector3().getDistance(
						-cameraTransformComponent->position) + 
						clipPlane.y * renderComponent->offset;
					//targetRenders.emplace(-glm::distance(-cameraTransform.position, glm::vec3(transformPosition)) + clipPlane.y * draw.offset, entity);
					break;
				case RenderComponent::Order::Front:
					order = -clipPlane.y + clipPlane.y * renderComponent->offset, render;
					break;
				case RenderComponent::Order::Back:
					order = clipPlane.y + clipPlane.y * renderComponent->offset, render;
					break;
				default:
					continue;
				}

				targetRenders.emplace(order, render);
			}

			for (auto& render : targetRenders)
			{
				auto renderComponent = render.second->getComponent<RenderComponent>();
				auto transformComponent = render.second->getComponent<TransformComponent>();

				auto& relative = transformComponent->parent;
				auto modelMatrix = transformComponent->matrix;

				while (relative)
				{
					TransformComponent* relativeTransform;

					if (!relative->getComponent(relativeTransform))
						break;

					modelMatrix = relativeTransform->matrix * modelMatrix;
					relative = relativeTransform->parent;
				}

				auto mvpMatrix = viewProjMatrix * modelMatrix;
				auto& material = renderComponent->material;

				material->use();

				material->setModelMatrix(modelMatrix);
				material->setViewMatrix(viewMatrix);
				material->setProjMatrix(projMatrix);
				material->setViewProjMatrix(viewProjMatrix);
				material->setMvpMatrix(mvpMatrix);

				//draw.mesh->bind();
				//draw.mesh->draw(draw.drawMode);
				//draw.mesh->unbind();

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
}
