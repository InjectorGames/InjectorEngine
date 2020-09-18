#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/GlGpuMesh.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Graphics/GlGpuShader.hpp"
#include "Injector/Exception/CastException.hpp"
#include "Injector/Graphics/GlCameraSystem.hpp"
#include "Injector/Graphics/GlRenderSystem.hpp"
#include "Injector/Graphics/GlColColorGpuPipeline.hpp"
#include "Injector/Graphics/GlTexDiffuseGpuPipeline.hpp"

namespace Injector
{
	GLFWwindow* GlWindow::createWindow(
		bool gles,
		const std::string& title,
		const IntVector2& size)
	{
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

		return glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
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
			throw Exception("GlWindow", "GlWindow", "Failed to initialize GLEW");

		glfwSwapInterval(0);
	}
	GlWindow::~GlWindow()
	{}

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
		auto usage = mappable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
		return std::make_shared<GlGpuBuffer>(type, size, usage, data);
	}
	std::shared_ptr<GpuMesh> GlWindow::createMesh(
		size_t indexCount,
		GpuBufferIndex indexType,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer)
	{
		return std::make_shared<GlGpuMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
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
        int size,
        GpuImageFormat format,
        GpuImageFilter minFilter,
    	GpuImageFilter magFilter,
    	GpuImageWrap wrapU,
        bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return std::make_shared<GlGpuImage>(GpuImageType::Image1D, IntVector3(size, 0, 0), format,
			minFilter, magFilter, wrapU, GpuImageWrap::Repeat, GpuImageWrap::Repeat, useMipmap, data);
	}
	std::shared_ptr<GpuImage> GlWindow::createImage(
        const IntVector2& size,
        GpuImageFormat format,
        GpuImageFilter minFilter,
    	GpuImageFilter magFilter,
    	GpuImageWrap wrapU,
        GpuImageWrap wrapV,
        bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return std::make_shared<GlGpuImage>(GpuImageType::Image2D, IntVector3(size, 0), format,
			minFilter, magFilter, wrapU, wrapV, GpuImageWrap::Repeat, useMipmap, data);
	}
	std::shared_ptr<GpuImage> GlWindow::createImage(
        const IntVector3& size,
        GpuImageFormat format,
        GpuImageFilter minFilter,
    	GpuImageFilter magFilter,
    	GpuImageWrap wrapU,
        GpuImageWrap wrapV,
        GpuImageWrap wrapW,
        bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return std::make_shared<GlGpuImage>(GpuImageType::Image3D, size, format,
			minFilter, magFilter, wrapU, wrapV, wrapW, useMipmap, data);
	}

	std::shared_ptr<ColorGpuPipeline> GlWindow::createColorPipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		if(!glVertexShader || !glFragmentShader)
			throw CastException("GlWindow", "createColorPipeline", "shader"); 

		return std::make_shared<GlColorGpuPipeline>(
			glVertexShader, glFragmentShader);
	}
	std::shared_ptr<ColorGpuPipeline> GlWindow::createColColorPipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		if(!glVertexShader || !glFragmentShader)
			throw CastException("GlWindow", "createColColorPipeline", "shader"); 

		return std::make_shared<GlColColorGpuPipeline>(
			glVertexShader, glFragmentShader);
	}
	std::shared_ptr<DiffuseGpuPipeline> GlWindow::createDiffusePipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);

		if(!glVertexShader || !glFragmentShader)
			throw CastException("GlWindow", "createDiffusePipeline", "shader"); 

		return std::make_shared<GlDiffuseGpuPipeline>(
			glVertexShader, glFragmentShader);
	}
	std::shared_ptr<TexDiffuseGpuPipeline> GlWindow::createTexDiffusePipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& texture)
	{
		auto glVertexShader = std::dynamic_pointer_cast<GlGpuShader>(vertexShader);
		auto glFragmentShader = std::dynamic_pointer_cast<GlGpuShader>(fragmentShader);
		auto glTexture = std::dynamic_pointer_cast<GlGpuImage>(texture);

		if(!glVertexShader || !glFragmentShader || !glTexture)
			throw CastException("GlWindow", "createTexDiffusePipeline", "shader/texture"); 
			
		return std::make_shared<GlTexDiffuseGpuPipeline>(
			glVertexShader, glFragmentShader, glTexture);
	}
}
