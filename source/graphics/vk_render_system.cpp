#include <injector/graphics/vk_render_system.hpp>
#include <injector/graphics/vk_window.hpp>
#include <injector/graphics/vk_pipeline.hpp>
#include <injector/graphics/vk_mesh.hpp>

#include <map>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkRenderSystem::VkRenderSystem(
		VkWindow& _window) :
		window(_window)
	{
	}
	VkRenderSystem::~VkRenderSystem()
	{}

	void VkRenderSystem::update()
	{
		struct CameraData
		{
			CameraComponent* camera;
			TransformComponent* transform;
		};

		auto renderCameras = std::multimap<int, CameraData>();

		for (auto& camera : cameras)
		{
			auto data = CameraData();

			if (!camera->getComponent(data.camera) ||
				!camera->getComponent(data.transform))
				continue;

			renderCameras.emplace(data.camera->queue, data);
		}

		struct RenderData
		{
			VkMeshHandle mesh;
			TransformComponent* transform;
		};

		auto renderPairs = std::multimap<VkPipelineHandle, RenderData>();

		for (auto& render : renders)
		{
			RenderComponent* renderComponent;
			auto data = RenderData();

			if (!render->getComponent<RenderComponent>(renderComponent) ||
				!render->getComponent<TransformComponent>(data.transform) ||
				!renderComponent->render ||
				!renderComponent->pipeline ||
				!renderComponent->mesh)
				continue;

			auto pipeline = std::dynamic_pointer_cast<VkPipeline>(
				renderComponent->pipeline);
			data.mesh = std::dynamic_pointer_cast<VkMesh>(
				renderComponent->mesh);

			if (!pipeline || !data.mesh)
				continue;

			renderPairs.emplace(pipeline, data);
		}

		auto imageIndex = window.beginImage();
		auto commandBuffer = window.getGraphicsCommandBuffer(imageIndex);
		window.beginRecord(imageIndex);

		for (auto cameraPair : renderCameras)
		{
			auto& viewMatrix = cameraPair.second.transform->matrix;
			auto& projMatrix = cameraPair.second.camera->matrix;
			auto viewProjMatrix = projMatrix * viewMatrix;

			VkPipelineHandle lastPipeline = nullptr;

			for (auto renderPair : renderPairs)
			{
				auto& modelMatrix = renderPair.second.transform->matrix;
				auto mvpMatrix = modelMatrix;

				if (lastPipeline != renderPair.first)
				{
					lastPipeline = renderPair.first;
					renderPair.first->setMVP(mvpMatrix);
					renderPair.first->bind(commandBuffer);
				}

				renderPair.second.mesh->draw(commandBuffer);
			}
		}

		window.endRecord(imageIndex);
		window.endImage(imageIndex);

		/*

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
