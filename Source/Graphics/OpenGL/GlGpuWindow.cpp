#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"
#include "Injector/Graphics/OpenGL/GlGpuMesh.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/CastException.hpp"
#include "Injector/Graphics/ImguiDefines.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"
#include "Injector/Graphics/OpenGL/GlGpuFramebuffer.hpp"
#include "Injector/Graphics/OpenGL/GlRenderEcsSystem.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlGuiGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlColorColorGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlImageDiffuseGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/Pipeline/GlSimulatedSkyGpuPipeline.hpp"

#include <iostream>

namespace Injector
{
	GLFWwindow* GlGpuWindow::createWindow(
		bool gles,
		const std::string& title,
		const SizeVector2& size)
	{
		if(size.x < 1 || size.y < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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
			static_cast<int>(size.x),
			static_cast<int>(size.y),
			title.c_str(),
			nullptr,
			nullptr);
	}

	GlGpuWindow::GlGpuWindow(
		bool _gles,
		const std::string& title,
		const SizeVector2& size) :
		GpuWindow(createWindow(_gles, title, size)),
		gles(_gles),
		lastFramebufferSize(),
		pipelines()
	{
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to initialize GLEW");
		}

		ImGui_ImplGlfw_InitForOpenGL(
			window,
			false);
	}
	GlGpuWindow::~GlGpuWindow()
	{
		ImGui_ImplGlfw_Shutdown();
	}

	bool GlGpuWindow::isGLES() const noexcept
	{
		return gles;
	}

	void GlGpuWindow::onUpdate()
	{
		GpuWindow::onUpdate();

		auto newFramebufferSize = getFramebufferSize();

		if (newFramebufferSize.x == 0 ||
			newFramebufferSize.y == 0)
		{
			return;
		}

		glfwMakeContextCurrent(window);

		if (lastFramebufferSize != newFramebufferSize)
		{
			glViewport(
				0,
				0,
				newFramebufferSize.x,
				newFramebufferSize.y);
		}

		glClearColor(
			0.0f,
			0.0f,
			0.0f,
			1.0f);
		glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT);

		for (auto& system : systems)
		{
			auto graphicsSystem = std::dynamic_pointer_cast<
				GraphicsEcsSystem>(system);

			if (graphicsSystem)
				graphicsSystem->onRender();
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

		glfwSwapBuffers(window);
	}

	bool GlGpuWindow::addPipeline(
		const std::shared_ptr<GpuPipeline>& pipeline)
	{
		auto glPipeline = std::dynamic_pointer_cast<
			GlGpuPipeline>(pipeline);

		if (!glPipeline)
			return false;

		return pipelines.emplace(glPipeline).second;
	}
	bool GlGpuWindow::removePipeline(
		const std::shared_ptr<GpuPipeline>& pipeline)
	{
		auto glPipeline = std::dynamic_pointer_cast<
			GlGpuPipeline>(pipeline);

		if (!glPipeline)
			return false;

		auto iterator = pipelines.find(glPipeline);

		if (iterator == pipelines.end())
			return false;

		pipelines.erase(iterator);
		return true;
	}

	std::shared_ptr<GpuBuffer> GlGpuWindow::createBuffer(
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
	std::shared_ptr<GpuMesh> GlGpuWindow::createMesh(
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
	std::shared_ptr<ShaderData> GlGpuWindow::readShaderData(
		const std::string& filePath)
	{
		auto fileStream = FileStream(filePath, std::ios::in);

		if (!fileStream.is_open())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to open shader file '" +
					std::string(filePath) + "'");
		}

		auto shaderDataSize = fileStream.getSize();
		auto shaderData = std::make_shared<ShaderData>();
		shaderData->code = std::vector<uint8_t>(shaderDataSize + 1);

		fileStream.read(
			shaderData->code.data(),
			shaderDataSize);

		shaderData->code[shaderDataSize] = 0;
		return shaderData;
	}
	std::shared_ptr<GpuShader> GlGpuWindow::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		return std::make_shared<GlGpuShader>(gles, stage, data);
	}
	std::shared_ptr<GpuImage> GlGpuWindow::createImage(
		GpuImageType type,
		GpuImageFormat format,
		const SizeVector3& size,
		bool useMipmap,
		const void* data)
	{
		return std::make_shared<GlGpuImage>(
			type,
			format,
			size,
			useMipmap,
			data);
	}
	std::shared_ptr<GpuFramebuffer> GlGpuWindow::createFramebuffer(
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

	std::shared_ptr<GpuPipeline> GlGpuWindow::createColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& color)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<GlColorGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			color);

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
	std::shared_ptr<GpuPipeline> GlGpuWindow::createColorColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& color)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<GlColorColorGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			color);

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
	std::shared_ptr<GpuPipeline> GlGpuWindow::createDiffusePipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const FloatVector4& objectColor,
		const FloatVector4& ambientColor,
		const FloatVector4& lightColor,
		const FloatVector3& lightDirection)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<GlDiffuseGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			GlDiffuseGpuPipeline::UniformBufferObject(
				objectColor,
				ambientColor,
				lightColor,
				lightDirection));

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
	std::shared_ptr<GpuPipeline> GlGpuWindow::createImageDiffusePipeline(
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
		const FloatVector4& objectColor,
		const FloatVector4& ambientColor,
		const FloatVector4& lightColor,
		const FloatVector3& lightDirection,
		const FloatVector2& imageScale,
		const FloatVector2& imageOffset)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);
		auto glImage = std::dynamic_pointer_cast<GlGpuImage>(image);

		auto pipeline = std::make_shared<GlImageDiffuseGpuPipeline>(
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

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
	std::shared_ptr<GpuPipeline> GlGpuWindow::createGuiPipeline(
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
		const FloatVector2& imageScale,
		const FloatVector2& imageOffset)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);
		auto glImage = std::dynamic_pointer_cast<GlGpuImage>(image);

		auto pipeline = std::make_shared<GlGuiGpuPipeline>(
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
			imageScale,
			imageOffset);

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
	std::shared_ptr<GpuPipeline> GlGpuWindow::createSkyPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		// TODO:
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		auto pipeline = std::make_shared<GlSimulatedSkyGpuPipeline>(
			drawMode,
			glVertexShader,
			glFragmentShader,
			GlSimulatedSkyGpuPipeline::UniformBufferObject(0.0f));

		if (!pipelines.emplace(pipeline).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to emplace");
		}

		return std::move(pipeline);
	}
}
