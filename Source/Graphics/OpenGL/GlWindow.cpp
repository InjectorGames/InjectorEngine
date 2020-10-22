#include "Injector/Graphics/OpenGL/GlWindow.hpp"
#include "Injector/Graphics/OpenGL/GlGpuMesh.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"
#include "Injector/Exception/CastException.hpp"
#include "Injector/Graphics/OpenGL/GlCameraSystem.hpp"
#include "Injector/Graphics/OpenGL/GlRenderSystem.hpp"
#include "Injector/Graphics/OpenGL/GlGpuFramebuffer.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlSimulatedSkyGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlColorColorGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlImageDiffuseGpuPipeline.hpp"

namespace Injector
{
	GLFWwindow* GlWindow::createWindow(
		bool gles,
		const std::string& title,
		const IntVector2& size)
	{
		if(size.x < 1 || size.y < 0)
		{
			throw Exception(
				"GlWindow",
				"GlWindow",
				"Incorrect size");
		}

		glfwDefaultWindowHints();

		glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		if (gles)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		}
		else
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		}

		return glfwCreateWindow(
			size.x,
			size.y,
			title.c_str(),
			nullptr,
			nullptr);
	}

	GlWindow::GlWindow(
		bool _gles,
		const std::string& title,
		const IntVector2& position) :
		Window(createWindow(_gles, title, position)),
		gles(_gles)
	{
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			throw Exception(
				"GlWindow",
				"GlWindow",
				"Failed to initialize GLEW");
		}

		glfwSwapInterval(0);
	}

	bool GlWindow::isGLES() const noexcept
	{
		return gles;
	}

	void GlWindow::makeCurrent() noexcept
	{
		glfwMakeContextCurrent(window);
	}
	void GlWindow::swapBuffers() noexcept
	{
		glfwSwapBuffers(window);
	}

	void GlWindow::onFramebufferResize(const IntVector2& size)
	{
		glfwMakeContextCurrent(window);
		glViewport(0, 0, size.x, size.y);
	}

	std::shared_ptr<CameraSystem> GlWindow::createCameraSystem()
	{
		auto system = std::make_shared<GlCameraSystem>(*this);
		systems.push_back(system);
		return system;
	}
	std::shared_ptr<RenderSystem> GlWindow::createRenderSystem()
	{
		auto system = std::make_shared<GlRenderSystem>(*this);
		systems.push_back(system);
		return system;
	}

	std::shared_ptr<GpuBuffer> GlWindow::createBuffer(
		size_t size,
		GpuBufferType type,
		bool mappable,
		const void* data)
	{
		auto usage = mappable ?
			GL_DYNAMIC_DRAW :
			GL_STATIC_DRAW;

		return std::make_shared<GlGpuBuffer>(
			type,
			size,
			usage,
			data);
	}
	std::shared_ptr<GpuMesh> GlWindow::createMesh(
		size_t indexCount,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer)
	{
		auto glVertexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(vertexBuffer);
		auto glIndexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(indexBuffer);

		return std::make_shared<GlGpuMesh>(
			indexCount,
			glVertexBuffer,
			glIndexBuffer);
	}
	std::shared_ptr<ShaderData> GlWindow::readShaderData(
		const std::string& filePath)
	{
		auto fileStream = FileStream(filePath, std::ios::in);
		auto shaderData = std::make_shared<ShaderData>();
		shaderData->code = std::vector<uint8_t>(fileStream.getSize() + 1);
		fileStream.read(shaderData->code.data(), fileStream.getSize());
		shaderData->code[fileStream.getSize() - 1] = 0;
		return shaderData;
	}
	std::shared_ptr<GpuShader> GlWindow::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		return std::make_shared<GlGpuShader>(gles, stage, data);
	}
	std::shared_ptr<GpuImage> GlWindow::createImage(
		GpuImageType type,
		GpuImageFormat format,
		const IntVector3& size,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return std::make_shared<GlGpuImage>(
			type,
			format,
			size,
			useMipmap,
			data);
	}
	std::shared_ptr<GpuFramebuffer> GlWindow::createFramebuffer(
		const std::shared_ptr<GpuImage>& colorImage,
		const std::shared_ptr<GpuImage>& depthImage,
		const std::shared_ptr<GpuImage>& stencilImage)
	{
		auto glColorImage = std::dynamic_pointer_cast<GlGpuImage>(colorImage);
		auto glDepthImage = std::dynamic_pointer_cast<GlGpuImage>(depthImage);
		auto glStencilImage = std::dynamic_pointer_cast<GlGpuImage>(stencilImage);

		return std::make_shared<GlGpuFramebuffer>(
			glColorImage,
			glDepthImage,
			glStencilImage);
	}

	std::shared_ptr<GpuPipeline> GlWindow::createColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const Vector4& color)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		return std::make_shared<GlColorGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			color);
	}
	std::shared_ptr<GpuPipeline> GlWindow::createColorColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const Vector4& color)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		return std::make_shared<GlColorColorGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			color);
	}
	std::shared_ptr<GpuPipeline> GlWindow::createDiffusePipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		return std::make_shared<GlDiffuseGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			GlDiffuseGpuPipeline::UniformBufferObject(
				objectColor,
				ambientColor,
				lightColor,
				lightDirection));
	}
	std::shared_ptr<GpuPipeline> GlWindow::createImageDiffusePipeline(
		GpuDrawMode drawMode,
		GpuImageFilter imageMinFilter,
		GpuImageFilter imageMagFilter,
		GpuImageFilter mipmapFilter,
		GpuImageWrap imageWrapU,
		GpuImageWrap imageWrapV,
		GpuImageWrap imageWrapW,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& image,
		const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection,
		const Vector2& imageScale,
		const Vector2& imageOffset)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);
		auto glImage = std::dynamic_pointer_cast<GlGpuImage>(image);

		return std::make_shared<GlImageDiffuseGpuPipeline>(
			drawMode,
			imageMinFilter,
			imageMagFilter,
			mipmapFilter,
			imageWrapU,
			imageWrapV,
			imageWrapW,
			glVertexShader,
			glFragmentShader,
			glImage,
			GlImageDiffuseGpuPipeline::UniformBufferObject(
				objectColor,
				ambientColor,
				lightColor,
				lightDirection,
				imageScale,
				imageOffset));
	}
	std::shared_ptr<GpuPipeline> GlWindow::createSkyPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		return std::make_shared<GlSimulatedSkyGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			GlSimulatedSkyGpuPipeline::UniformBufferObject(0.0f));
	}
}
