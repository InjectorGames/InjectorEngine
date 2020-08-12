#include <injector/graphics/vk_render_system.hpp>
#include <injector/graphics/vk_window.hpp>
#include <injector/graphics/vk_mesh.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkRenderSystem::VkRenderSystem(
		const VkWindowHandle& _window) :
		window(_window)
	{
		if (!window)
			throw std::runtime_error("Vulkan render system window is null");
	}
	VkRenderSystem::~VkRenderSystem()
	{}

	WindowHandle VkRenderSystem::getWindow() const
	{
		return window;
	}

	void VkRenderSystem::update()
	{
		auto imageIndex = window->beginImage();
		auto commandBuffer = window->getGraphicsCommandBuffer(imageIndex);
		window->beginRecord(imageIndex);

		for (auto& render : renders)
		{
			RenderComponent* renderComponent;

			if (!render->getComponent<RenderComponent>(renderComponent) ||
				!renderComponent->render || !renderComponent->mesh)
				continue;

			auto vkMesh = std::dynamic_pointer_cast<VkMesh>(renderComponent->mesh);

			if (!vkMesh)
				continue;

			vkMesh->draw(commandBuffer);
		}

		window->endRecord(imageIndex);
		window->endImage(imageIndex);
		

		/*std::multimap<int, EntityHandle> targetCameras;

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

				auto commandBuffer = commandBuffers[frameIndex];
				commandBuffer.bindVertexBuffers(0, 1, vertexBuffer->)

				vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
				vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT16);
				graphicsCommandBuffer.draw(3, 1, 0, 0);

				material->unuse();
				//drawCount++;
			}
		}*/
	}
}
