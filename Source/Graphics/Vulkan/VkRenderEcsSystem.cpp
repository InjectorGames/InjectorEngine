#include "Injector/Graphics/Vulkan/VkRenderEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Graphics/Vulkan/VkGpuMesh.hpp"
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"

#include <map>

namespace Injector
{
	VkRenderEcsSystem::VkRenderEcsSystem(
		const std::shared_ptr<VkGpuWindow>& _window) :
		window(_window)
	{
		if(!_window)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"window");
		}
	}

	const std::shared_ptr<VkGpuWindow>&
	    VkRenderEcsSystem::getWindow() const noexcept
	{
		return window;
	}

	void VkRenderEcsSystem::onUpdate()
	{
		if (window->isMinimized())
			return;

		struct CameraData
		{
			CameraEcsComponent* camera;
			TransformEcsComponent* transform;
		};

		struct RenderData
		{
			std::shared_ptr<VkGpuPipeline> pipeline;
			std::shared_ptr<VkGpuMesh> mesh;
			TransformEcsComponent* transform;
		};

		auto cameraPairs = std::multimap<int, CameraData>();

		for (auto& camera : cameras)
		{
			auto cameraData = CameraData();

			if (!camera->getComponent(cameraData.camera) ||
				!camera->getComponent(cameraData.transform) ||
				!cameraData.camera->render)
				continue;

			cameraPairs.emplace(
				cameraData.camera->renderQueue,
				cameraData);
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
				RenderEcsComponent* renderComponent;

				if (!render->getComponent<RenderEcsComponent>(renderComponent) ||
					!render->getComponent<TransformEcsComponent>(renderData.transform) ||
					!renderComponent->render ||
					!renderComponent->pipeline ||
					!renderComponent->mesh)
					continue;

				if (renderData.transform->parent)
				{
					auto parent = renderData.transform->parent;
					TransformEcsComponent* parentTransformComponent;

					auto shouldRender = true;
					auto cycleCount = 0;

					while (parent)
					{
						RenderEcsComponent* parentRenderComponent;

						if (!parent->getComponent(parentTransformComponent) ||
							!parent->getComponent(parentRenderComponent))
							break;

						parent = parentTransformComponent->parent;

						if(!parentRenderComponent->render)
						{
							shouldRender = false;
							break;
						}

						if (cycleCount > 0xFFFF)
						{
							throw OutOfRangeException(
								THIS_FUNCTION_NAME,
								cycleCount,
								0xFFFF);
						}
						else
						{
							cycleCount++;
						}
					}

					if(!shouldRender)
						continue;
				}

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
