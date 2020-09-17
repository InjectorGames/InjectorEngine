#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Exception/CastException.hpp"
#include "Injector/Graphics/GlMesh.hpp"
#include "Injector/Graphics/GlCameraSystem.hpp"
#include "Injector/Graphics/GlRenderSystem.hpp"
#include "Injector/Graphics/GlColColorPipeline.hpp"
#include "Injector/Graphics/GlTexDiffusePipeline.hpp"

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

	std::shared_ptr<Buffer> GlWindow::createBuffer(
		size_t size,
		BufferType type,
		bool mappable,
		const void* data)
	{
		auto usage = mappable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
		return std::make_shared<GlBuffer>(type, size, usage, data);
	}
	std::shared_ptr<Mesh> GlWindow::createMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer)
	{
		return std::make_shared<GlMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Texture> GlWindow::createTexture(
        int size,
        TextureFormat format,
        TextureFilter minFilter,
    	TextureFilter magFilter,
    	TextureWrap wrapU,
        bool useMipmap,
		const std::shared_ptr<Image>& image)
	{
		return std::make_shared<GlTexture>(TextureType::T1D, IntVector3(size, 0, 0), format,
			minFilter, magFilter, wrapU, TextureWrap::Repeat, TextureWrap::Repeat, useMipmap, image);
	}
	std::shared_ptr<Texture> GlWindow::createTexture(
        const IntVector2& size,
        TextureFormat format,
        TextureFilter minFilter,
    	TextureFilter magFilter,
    	TextureWrap wrapU,
        TextureWrap wrapV,
        bool useMipmap,
		const std::shared_ptr<Image>& image)
	{
		return std::make_shared<GlTexture>(TextureType::T2D, IntVector3(size, 0), format,
			minFilter, magFilter, wrapU, wrapV, TextureWrap::Repeat, useMipmap, image);
	}
	std::shared_ptr<Texture> GlWindow::createTexture(
        const IntVector3& size,
        TextureFormat format,
        TextureFilter minFilter,
    	TextureFilter magFilter,
    	TextureWrap wrapU,
        TextureWrap wrapV,
        TextureWrap wrapW,
        bool useMipmap,
		const std::shared_ptr<Image>& image)
	{
		return std::make_shared<GlTexture>(TextureType::T3D, size, format,
			minFilter, magFilter, wrapU, wrapV, wrapW, useMipmap, image);
	}

	std::shared_ptr<ColorPipeline> GlWindow::createColorPipeline()
	{
		return std::make_shared<GlColorPipeline>(gles);
	}
	std::shared_ptr<ColorPipeline> GlWindow::createColColorPipeline()
	{
		return std::make_shared<GlColColorPipeline>(gles);
	}
	std::shared_ptr<DiffusePipeline> GlWindow::createDiffusePipeline()
	{
		return std::make_shared<GlDiffusePipeline>(gles);
	}
	std::shared_ptr<TexDiffusePipeline> GlWindow::createTexDiffusePipeline(
		const std::shared_ptr<Texture>& texture)
	{
		auto glTexture = std::dynamic_pointer_cast<GlTexture>(texture);

		if(!glTexture)
			throw CastException("GlWindow", "createTexDiffusePipeline", "texture"); 
			
		return std::make_shared<GlTexDiffusePipeline>(gles, glTexture);
	}
}
