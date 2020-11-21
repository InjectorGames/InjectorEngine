#include "Injector/Graphics/OpenGL/GlRenderEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Graphics/OpenGL/GlGpuMesh.hpp"

#include <map>
#include <iostream>

namespace Injector
{
	GlRenderEcsSystem::GlRenderEcsSystem(
		const std::shared_ptr<GlGpuWindow>& _window) :
		window(_window)
	{
		if(!_window)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"window");
		}
	}

	const std::shared_ptr<GlGpuWindow>&
	    GlRenderEcsSystem::getWindow() const noexcept
	{
		return window;
	}

	void GlRenderEcsSystem::onUpdate()
	{
		struct CameraData
		{
			CameraEcsComponent* camera;
			TransformEcsComponent* transform;
		};
		struct RenderData
		{
			std::shared_ptr<GlGpuPipeline> pipeline;
			std::shared_ptr<GlGpuMesh> mesh;
			TransformEcsComponent* transform;
		};

		/*glClearColor(
			0.0f,
			0.0f, 
			0.0f, 
			1.0f);*/
		glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT);

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

				renderData.pipeline = std::dynamic_pointer_cast<GlGpuPipeline>(
					renderComponent->pipeline);
				renderData.mesh = std::dynamic_pointer_cast<GlGpuMesh>(
					renderComponent->mesh);

				if (!renderData.pipeline || !renderData.mesh)
					continue;

				auto distance = cameraData.transform->position.getDistance(
					-renderData.transform->position);
				renderPairs.emplace(distance, renderData);
				renderData.pipeline->flush();
			}

			auto& viewMatrix = cameraData.transform->matrix;
			auto& projMatrix = cameraData.camera->matrix;
			auto viewProjMatrix = projMatrix * viewMatrix;

			std::shared_ptr<GlGpuPipeline> lastPipeline = nullptr;

			for (auto& renderPair : renderPairs)
			{
				auto renderData = renderPair.second;

				auto& modelMatrix = renderData.transform->matrix;
				auto mvpMatrix = viewProjMatrix * modelMatrix;

				if (renderData.pipeline != lastPipeline)
				{
					lastPipeline = renderData.pipeline;
					renderData.pipeline->bind();
				}

				renderData.pipeline->setUniforms(
					modelMatrix,
					viewMatrix,
					projMatrix,
					viewProjMatrix,
					mvpMatrix);

				renderData.mesh->draw(renderData.pipeline);
			}
		}

#ifndef NDEBUG
		GLenum error;

		while((error = glGetError()) != GL_NO_ERROR)
		{
			switch (error)
			{
			case GL_INVALID_ENUM:
				std::cout << "Engine: OpenGL Error: GL_INVALID_ENUM\n";
				break;
			case GL_INVALID_VALUE:
				std::cout << "Engine: OpenGL Error: GL_INVALID_VALUE\n";
				break;
			case GL_INVALID_OPERATION:
				std::cout << "Engine: OpenGL Error: GL_INVALID_OPERATION\n";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cout << "Engine: OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION\n";
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "Engine: OpenGL Error: GL_OUT_OF_MEMORY\n";
				break;
			case GL_STACK_UNDERFLOW:
				std::cout << "Engine: OpenGL Error: GL_STACK_UNDERFLOW\n";
				break;
			case GL_STACK_OVERFLOW:
				std::cout << "Engine: OpenGL Error: GL_STACK_OVERFLOW\n";
				break;
			default:
				std::cout << "Engine: OpenGL Error: Unknown\n";
				break;
			}
		}
#endif
	}
}
