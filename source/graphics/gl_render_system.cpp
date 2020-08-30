#include <injector/graphics/gl_render_system.hpp>
#include <injector/graphics/gl_pipeline.hpp>
#include <injector/graphics/gl_mesh.hpp>

namespace INJECTOR_NAMESPACE
{
	GlRenderSystem::GlRenderSystem(GlWindow& _window) :
		window(_window)
	{}
	GlRenderSystem::~GlRenderSystem()
	{}

	void GlRenderSystem::update()
	{
		struct CameraData
		{
			CameraComponent* camera;
			TransformComponent* transform;
		};

		struct RenderData
		{
			GlPipelineHandle pipeline;
			GlMeshHandle mesh;
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

		window.makeCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

				renderData.pipeline = std::dynamic_pointer_cast<GlPipeline>(
					renderComponent->pipeline);
				renderData.mesh = std::dynamic_pointer_cast<GlMesh>(
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
				renderData.pipeline->bind();

				renderData.mesh->draw(GL_TRIANGLES,
					renderData.pipeline->getVertexAttributes());
			}
		}

		window.swapBuffers();
	}
}
