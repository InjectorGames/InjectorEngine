#include "Injector/Graphics/Window.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Graphics/VkWindow.hpp"
#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	const std::string Window::defaultTitle =
		"Injector Engine";
	const IntVector2 Window::defaultSize =
		IntVector2(800, 600);

	void Window::scrollCallback(
		GLFWwindow* window, double x, double y)
	{
		auto instance = static_cast<Window*>(
			glfwGetWindowUserPointer(window));
		instance->deltaScroll +=
			Vector2(static_cast<float>(x), static_cast<float>(y));
	}
	void Window::framebufferSizeCallback(
		GLFWwindow* window, int width, int height)
	{
		auto instance = static_cast<Window*>(
			glfwGetWindowUserPointer(window));
		instance->isResized = true;
	}

	Window::Window(
		GLFWwindow* _window) :
		window(_window),
		deltaScroll(),
		isResized()
	{
		if (!window)
		{
			throw NullException(
				"Window",
				"Window",
				"window");
		}

		glfwSetWindowUserPointer(
			window,
			this);
		glfwSetWindowSizeLimits(
			window,
			1,
			1,
			GLFW_DONT_CARE,
			GLFW_DONT_CARE);
		glfwSetScrollCallback(
			window,
			scrollCallback);
		glfwSetFramebufferSizeCallback(
			window,
			framebufferSizeCallback);

		if (glfwRawMouseMotionSupported() == GLFW_TRUE)
		{
			glfwSetInputMode(
				window,
				GLFW_RAW_MOUSE_MOTION,
				GLFW_TRUE);
		}

		cursor = glfwCreateStandardCursor(
			static_cast<int>(MouseIcon::Arrow));
		glfwSetCursor(window, cursor);
	}
	Window::~Window()
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}

	const Vector2& Window::getDeltaScroll() const noexcept
	{
		return deltaScroll;
	}

	void Window::update()
	{
		if (!glfwWindowShouldClose(window))
		{
			if (isResized)
			{
				auto size = getFramebufferSize();
				onFramebufferResize(size);
				isResized = false;
			}

			if (!isMinimized())
				Manager::update();

			deltaScroll = {};
			active = true;
		}
		else
		{
			active = false;
		}
	}
	void Window::onFramebufferResize(const IntVector2& size)
	{
		throw NotImplementedException(
			"Window",
			"onResize");
	}

	IntVector2 Window::getSize() const noexcept
	{
		auto size = IntVector2();
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}
	IntVector2 Window::getFramebufferSize() const noexcept
	{
		auto size = IntVector2();
		glfwGetFramebufferSize(window, &size.x, &size.y);
		return size;
	}
	IntVector2 Window::getPosition() const noexcept
	{
		auto size = IntVector2();
		glfwGetWindowPos(window, &size.x, &size.y);
		return size;
	}
	Vector2 Window::getMousePosition() const noexcept
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return Vector2(static_cast<float>(x), static_cast<int>(y));
	}
	ButtonState Window::getMouseButton(MouseButton button) const noexcept
	{
		return static_cast<ButtonState>(glfwGetMouseButton(
			window, static_cast<int>(button)));
	}
	ButtonState Window::getKeyboardButton(KeyboardButton button) const noexcept
	{
		return static_cast<ButtonState>(glfwGetKey(
			window, static_cast<int>(button)));
	}

	void Window::setSize(const IntVector2& size)
	{
		glfwSetWindowSize(window, size.x, size.y);
	}
	void Window::setSizeLimits(const IntVector2& min, const IntVector2& max)
	{
		if (min.x < 1 || min.y < 1 || max.x < 1 || max.y < 1)
		{
			throw Exception(
				"Window",
				"setSizeLimits",
				"Size can not be less than one");
		}

		glfwSetWindowSizeLimits(window, min.x, min.y, max.x, max.y);
	}
	void Window::setPosition(const IntVector2& position)
	{
		glfwSetWindowPos(window, position.x, position.y);
	}
	void Window::setTitle(const std::string& title)
	{
		glfwSetWindowTitle(window, title.c_str());
	}
	void Window::setIcons(const std::vector<std::shared_ptr<ImageData>>& icons)
	{
#if INJECTOR_SYSTEM_WINDOWS
		GLFWimage images[icons.size()];

		for (size_t i = 0; i < icons.size(); i++)
		{
			auto& icon = icons[i];
			auto& image = images[i];
			image.width = icon->psize.x;
			image.height = icon->psize.y;
			image.pixels = icon->pixels.data();
		}
		
		glfwSetWindowIcon(window, icons.size(), images);
#endif
	}
	void Window::setMouseMode(MouseMode mode)
	{
		glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
	}
	void Window::setMouseIcon(MouseIcon icon)
	{
		glfwSetCursor(window, nullptr);
		glfwDestroyCursor(cursor);

		cursor = glfwCreateStandardCursor(
			static_cast<int>(MouseIcon::Arrow));
		glfwSetCursor(window, cursor);
	}
	void Window::setMouseIcon(const std::shared_ptr<ImageData>& icon, const IntVector2& hotspot)
	{
		glfwSetCursor(window, nullptr);
		glfwDestroyCursor(cursor);

		auto image = GLFWimage();
		image.width = icon->size.x;
		image.height = icon->size.y;
		image.pixels = icon->pixels.data();

		cursor = glfwCreateCursor(&image, hotspot.x, hotspot.y);
		glfwSetCursor(window, cursor);
	}
	void Window::setResizable(bool resizable)
	{
		glfwSetWindowAttrib(
			window,
			GLFW_RESIZABLE,
			resizable ? GLFW_TRUE : GLFW_FALSE);
	}
	void Window::setDecorated(bool decorated)
	{
		glfwSetWindowAttrib(
			window,
			GLFW_DECORATED,
			decorated ? GLFW_TRUE : GLFW_FALSE);
	}

	bool Window::isFocused() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
	}
	bool Window::isMinimized() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_TRUE;
	}
	bool Window::isVisible() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_VISIBLE) == GLFW_TRUE;
	}
	bool Window::isResizable() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_RESIZABLE) == GLFW_TRUE;
	}
	bool Window::isDecorated() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_DECORATED) == GLFW_TRUE;
	}

	void Window::hide() noexcept
	{
		glfwHideWindow(window);
	}
	void Window::show() noexcept
	{
		glfwShowWindow(window);
	}
	void Window::minimize() noexcept
	{
		glfwIconifyWindow(window);
	}
	void Window::maximize() noexcept
	{
		glfwRestoreWindow(window);
	}
	void Window::focus() noexcept
	{
		glfwFocusWindow(window);
	}
	void Window::requestAttention() noexcept
	{
		glfwRequestWindowAttention(window);
	}

	std::shared_ptr<CameraSystem> Window::createCameraSystem()
	{
		throw NotImplementedException(
			"Window",
			"createCameraSystem");
	}
	std::shared_ptr<RenderSystem> Window::createRenderSystem()
	{
		throw NotImplementedException(
			"Window",
			"createRenderSystem");
	}

	std::shared_ptr<GpuBuffer> Window::createBuffer(
		size_t size,
		GpuBufferType type,
		bool mappable,
		const void* data)
	{
		throw NotImplementedException(
			"Window",
			"createBuffer");
	}
	std::shared_ptr<GpuMesh> Window::createMesh(
		size_t indexCount,
		GpuBufferIndex indexType,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer)
	{
		throw NotImplementedException(
			"Window",
			"createMesh");
	}
	std::shared_ptr<ShaderData> Window::readShaderData(
		const std::string& filePath)
	{
		throw NotImplementedException(
			"Window",
			"readShaderData");
	}
	std::shared_ptr<GpuShader> Window::createShader(
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data)
	{
		throw NotImplementedException(
			"Window",
			"createShader");
	}
	std::shared_ptr<GpuImage> Window::createImage(
		GpuImageType type,
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
		throw NotImplementedException(
			"Window",
			"createImage");
	}

	std::shared_ptr<ColorGpuPipeline> Window::createColorPipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		throw NotImplementedException(
			"Window",
			"createColorPipeline");
	}
	std::shared_ptr<ColorGpuPipeline> Window::createColColorPipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		throw NotImplementedException(
			"Window",
			"createColColorPipeline");
	}
	std::shared_ptr<DiffuseGpuPipeline> Window::createDiffusePipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		throw NotImplementedException(
			"Window",
			"createDiffusePipeline");
	}
	std::shared_ptr<TexDiffuseGpuPipeline> Window::createTexDiffusePipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& texture)
	{
		throw NotImplementedException(
			"Window",
			"createTexDiffusePipeline");
	}
	std::shared_ptr<SimSkyGpuPipeline> Window::createSkyPipeline(
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		throw NotImplementedException(
			"Window",
			"createSkyPipeline");
	}

	std::shared_ptr<GpuMesh> Window::createMesh(
		const std::vector<float>& vertices,
		bool mappableVertices,
		const std::vector<uint16_t>& indices,
		bool mappableIndices)
	{
		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			GpuBufferType::Vertex,
			mappableVertices,
			vertices.data());
		auto indexBuffer = createBuffer(
			indices.size() * sizeof(uint16_t),
			GpuBufferType::Index,
			mappableIndices,
			indices.data());

		return createMesh(
			indices.size(),
			GpuBufferIndex::UnsignedShort,
			vertexBuffer,
			indexBuffer);
	}
	std::shared_ptr<GpuMesh> Window::createMesh(
		const std::vector<float>& vertices,
		bool mappableVertices,
		const std::vector<uint32_t>& indices,
		bool mappableIndices)
	{
		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			GpuBufferType::Vertex,
			mappableVertices,
			vertices.data());
		auto indexBuffer = createBuffer(
			indices.size() * sizeof(uint32_t),
			GpuBufferType::Index,
			mappableIndices,
			indices.data());

		return createMesh(
			indices.size(),
			GpuBufferIndex::UnsignedInt,
			vertexBuffer,
			indexBuffer);
	}

	std::shared_ptr<GpuImage> Window::createImage(
		int size,
		GpuImageFormat format,
		GpuImageFilter minFilter,
		GpuImageFilter magFilter,
		GpuImageWrap wrapU,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return createImage(
			GpuImageType::Image1D,
			IntVector3(size, 0, 0),
			format,
			minFilter,
			magFilter,
			wrapU,
			GpuImageWrap::Repeat,
			GpuImageWrap::Repeat,
			useMipmap,
			data);
	}
	std::shared_ptr<GpuImage> Window::createImage(
		const IntVector2& size,
		GpuImageFormat format,
		GpuImageFilter minFilter,
		GpuImageFilter magFilter,
		GpuImageWrap wrapU,
		GpuImageWrap wrapV,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return createImage(
			GpuImageType::Image2D,
			IntVector3(size, 0),
			format,
			minFilter,
			magFilter,
			wrapU,
			wrapV,
			GpuImageWrap::Repeat,
			useMipmap,
			data);
	}
	std::shared_ptr<GpuImage> Window::createImage(
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
		return createImage(
			GpuImageType::Image3D,
			size,
			format,
			minFilter,
			magFilter,
			wrapU,
			wrapV,
			wrapW,
			useMipmap,
			data);
	}

	std::shared_ptr<Window> Window::create(
		const std::string& title,
		const IntVector2& size)
	{
		auto graphicsApi = Engine::getGraphicsApi();

		if (graphicsApi == GraphicsAPI::OpenGL)
		{
			return Engine::createManager<GlWindow>(
				false,
				title,
				size);
		}
		else if (graphicsApi == GraphicsAPI::OpenGLES)
		{
			return Engine::createManager<GlWindow>(
				true,
				title,
				size);
		}
		else if (graphicsApi == GraphicsAPI::Vulkan)
		{
			return Engine::createManager<VkWindow>(
				title,
				size);
		}
		else
		{
			throw Exception(
				"Window",
				"createWindow",
				"Unknown graphics API");
		}
	}
}