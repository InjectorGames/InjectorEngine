#include <injector/graphics/vk_render_system.hpp>
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

		struct RenderData
		{
			VkPipelineHandle pipeline;
			VkMeshHandle mesh;
			TransformComponent* transform;
		};

		auto cameraPairs = std::multimap<int, CameraData>();

		for (auto& camera : cameras)
		{
			auto cameraData = CameraData();

			if (!camera->getComponent(cameraData.camera) ||
				!camera->getComponent(cameraData.transform) ||
				!cameraData.camera->render)
				continue;

			cameraPairs.emplace(cameraData.camera->queue, cameraData);
		}

		auto imageIndex = window.beginImage();
		auto commandBuffer = window.getGraphicsCommandBuffer(imageIndex);
		window.beginRecord(imageIndex);

		for (auto& cameraPair : cameraPairs)
		{
			auto cameraData = cameraPair.second;
			auto renderPairs = std::multimap<float, RenderData>();

			for (auto& render : cameraData.camera->renders)
			{
				auto renderData = RenderData();
				RenderComponent* renderComponent;

				if (!render->getComponent<RenderComponent>(renderComponent) ||
					!render->getComponent<TransformComponent>(renderData.transform) ||
					!renderComponent->render ||
					!renderComponent->pipeline ||
					!renderComponent->mesh)
					continue;

				renderData.pipeline = std::dynamic_pointer_cast<VkPipeline>(
					renderComponent->pipeline);
				renderData.mesh = std::dynamic_pointer_cast<VkMesh>(
					renderComponent->mesh);

				if (!renderData.pipeline || !renderData.mesh)
					continue;

				auto distance = cameraData.transform->position.getDistance(
					-renderData.transform->position);
				renderPairs.emplace(distance, renderData);
			}

			auto& viewMatrix = cameraData.transform->matrix;
			auto& projMatrix = cameraData.camera->matrix;
			auto viewProjMatrix = projMatrix * viewMatrix;

			for (auto& renderPair : renderPairs)
			{
				auto renderData = renderPair.second;

				auto& modelMatrix = renderData.transform->matrix;
				auto mvpMatrix = viewProjMatrix * modelMatrix;

				renderData.pipeline->setModel(modelMatrix);
				renderData.pipeline->setView(viewMatrix);
				renderData.pipeline->setProj(projMatrix);
				renderData.pipeline->setViewProj(viewProjMatrix);
				renderData.pipeline->setMVP(mvpMatrix);
				renderData.pipeline->bind(imageIndex, commandBuffer);

				renderData.mesh->draw(commandBuffer);
			}
		}

		window.endRecord(imageIndex);
		window.endImage(imageIndex);
	}
}
