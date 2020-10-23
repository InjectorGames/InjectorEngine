#include "Injector/Graphics/Vulkan/VkRenderSystem.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/Vulkan/VkGpuMesh.hpp"
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"

#include <map>

namespace Injector
{
	VkRenderSystem::VkRenderSystem(
		const std::shared_ptr<VkWindow>& _window) :
		window(_window)
	{
		if(!_window)
		{
			throw NullException(
				"VkRenderSystem",
				"VkRenderSystem",
				"window");
		}
	}

	void VkRenderSystem::update()
	{
		if (window->isMinimized())
			return;

		struct CameraData
		{
			CameraComponent* camera;
			TransformComponent* transform;
		};

		struct RenderData
		{
			std::shared_ptr<VkGpuPipeline> pipeline;
			std::shared_ptr<VkGpuMesh> mesh;
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

		auto imageIndex = window->beginImage();
		auto commandBuffer = window->getGraphicsCommandBuffer(imageIndex);
		window->beginRecord(imageIndex);

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

				renderData.pipeline = std::dynamic_pointer_cast<VkGpuPipeline>(
					renderComponent->pipeline);
				renderData.mesh = std::dynamic_pointer_cast<VkGpuMesh>(
					renderComponent->mesh);

				if (!renderData.pipeline || !renderData.mesh)
					continue;

				auto distance = cameraData.transform->position.getDistance(
					-renderData.transform->position);
				renderPairs.emplace(distance, renderData);
				renderData.pipeline->flush(imageIndex);
			}

			auto& viewMatrix = cameraData.transform->matrix;
			auto& projMatrix = cameraData.camera->matrix;
			auto viewProjMatrix = projMatrix * viewMatrix;

			std::shared_ptr<VkGpuPipeline> lastPipeline = nullptr;

			for (auto& renderPair : renderPairs)
			{
				auto renderData = renderPair.second;

				auto& modelMatrix = renderData.transform->matrix;
				auto mvpMatrix = viewProjMatrix * modelMatrix;

				if (renderData.pipeline != lastPipeline)
				{
					lastPipeline = renderData.pipeline;
					renderData.pipeline->bind(commandBuffer, imageIndex);
				}

				renderData.pipeline->setUniforms(
					modelMatrix,
					viewMatrix,
					projMatrix,
					viewProjMatrix,
					mvpMatrix);

				renderData.mesh->draw(commandBuffer);
			}
		}

		window->endRecord(imageIndex);
		window->endImage(imageIndex);
	}
}
