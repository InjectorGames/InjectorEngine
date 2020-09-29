#include "Injector/Graphics/GlRenderSystem.hpp"
#include "Injector/Graphics/GlGpuMesh.hpp"

#include <map>

namespace Injector
{
	GlRenderSystem::GlRenderSystem(GlWindow& _window) :
		window(_window)
	{
		// TMP:
		uint32_t x, y;
		vr::VRSystem()->GetRecommendedRenderTargetSize(&x, &y);

		window.setSize(IntVector2(x, y));

		auto colorImage = std::make_shared<GlGpuImage>(
			GpuImageType::Image2D,
			IntVector3(x, y, 0),
			GpuImageFormat::RGBA8F,
			GpuImageFilter::Nearest,
			GpuImageFilter::Nearest,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			false,
			nullptr);
		leftTexture = colorImage->getTexture();
		auto depthStencilImage = std::make_shared<GlGpuImage>(
			GpuImageType::Image2D,
			IntVector3(x, y, 0),
			GpuImageFormat::Depth24Stencil8,
			GpuImageFilter::Nearest,
			GpuImageFilter::Nearest,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			false,
			nullptr);
		leftFramebuffer = std::make_shared<GlGpuFramebuffer>(
			colorImage,
			depthStencilImage,
			depthStencilImage);

		colorImage = std::make_shared<GlGpuImage>(
				GpuImageType::Image2D,
				IntVector3(x, y, 0),
				GpuImageFormat::RGBA8F,
				GpuImageFilter::Linear,
				GpuImageFilter::Linear,
				GpuImageWrap::Repeat,
				GpuImageWrap::Repeat,
				GpuImageWrap::Repeat,
				false,
				nullptr);
		rightTexture = colorImage->getTexture();
		depthStencilImage = std::make_shared<GlGpuImage>(
			GpuImageType::Image2D,
			IntVector3(x, y, 0),
			GpuImageFormat::Depth24Stencil8,
			GpuImageFilter::Linear,
			GpuImageFilter::Linear,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			false,
			nullptr);
		rightFramebuffer = std::make_shared<GlGpuFramebuffer>(
			colorImage,
			depthStencilImage,
			depthStencilImage);
	}
	GlRenderSystem::~GlRenderSystem()
	{
	}

	void GlRenderSystem::draw()
	{
		struct CameraData
		{
			CameraComponent* camera;
			TransformComponent* transform;
		};

		struct RenderData
		{
			std::shared_ptr<GlGpuPipeline> pipeline;
			std::shared_ptr<GlGpuMesh> mesh;
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
	}

	void GlRenderSystem::update()
	{
		if (window.isMinimized())
			return;

		uint32_t x, y;
		vr::VRSystem()->GetRecommendedRenderTargetSize(&x, &y);

		window.makeCurrent();
		glViewport(0, 0, x, y);

		leftFramebuffer->bind();
		glViewport(0, 0, x, y);

		glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT);

		draw();
		leftFramebuffer->unbind();

		rightFramebuffer->bind();
		glViewport(0, 0, x, y);

		glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT);

		draw();
		rightFramebuffer->unbind();

		vr::Texture_t leftEyeTexture = {(void*)(uintptr_t)leftTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);

		vr::Texture_t rightEyeTexture = {(void*)(uintptr_t)rightTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, leftFramebuffer->getFramebuffer());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GL_ZERO);

		glBlitFramebuffer(0, 0, x, y, 0, 0, x, y,
			GL_COLOR_BUFFER_BIT,
			GL_LINEAR);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, GL_ZERO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GL_ZERO);

		window.swapBuffers();
	}
}
