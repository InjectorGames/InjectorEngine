#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"
#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	const std::string GpuWindow::defaultTitle =
		"Injector Engine";
	const IntVector2 GpuWindow::defaultSize =
		IntVector2(800, 600);

	void GpuWindow::scrollCallback(
		GLFWwindow* window,
		double x,
		double y)
	{
		auto instance = static_cast<GpuWindow*>(
			glfwGetWindowUserPointer(window));
		instance->deltaScroll +=
			Vector2(static_cast<float>(x), static_cast<float>(y));
	}
	void GpuWindow::framebufferSizeCallback(
		GLFWwindow* window,
		int width,
		int height)
	{
		auto instance = static_cast<GpuWindow*>(
			glfwGetWindowUserPointer(window));
		instance->isResized = true;
	}

	GpuWindow::GpuWindow(
		GLFWwindow* _window) :
		window(_window),
		deltaScroll(),
		isResized()
	{
		if (!window)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
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
	GpuWindow::~GpuWindow()
	{
		glfwDestroyWindow(window);
	}

	const Vector2& GpuWindow::getDeltaScroll() const noexcept
	{
		return deltaScroll;
	}

	void GpuWindow::update()
	{
		if (!glfwWindowShouldClose(window))
		{
			if (isResized)
			{
				auto size = getFramebufferSize();

				if (size.x > 0 && size.y > 0)
					onFramebufferResize(size);

				isResized = false;
			}

			EcsManager::update();

			deltaScroll = {};
			active = true;
		}
		else
		{
			active = false;
		}
	}

	IntVector2 GpuWindow::getSize() const noexcept
	{
		auto size = IntVector2();
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}
	IntVector2 GpuWindow::getFramebufferSize() const noexcept
	{
		auto size = IntVector2();
		glfwGetFramebufferSize(window, &size.x, &size.y);
		return size;
	}
	IntVector2 GpuWindow::getPosition() const noexcept
	{
		auto size = IntVector2();
		glfwGetWindowPos(window, &size.x, &size.y);
		return size;
	}
	Vector2 GpuWindow::getMousePosition() const noexcept
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}
	ButtonState GpuWindow::getMouseButton(MouseButton button) const noexcept
	{
		return static_cast<ButtonState>(glfwGetMouseButton(
			window, static_cast<int>(button)));
	}
	ButtonState GpuWindow::getKeyboardButton(KeyboardButton button) const noexcept
	{
		return static_cast<ButtonState>(glfwGetKey(
			window, static_cast<int>(button)));
	}

	void GpuWindow::setSize(const IntVector2& size)
	{
		glfwSetWindowSize(window, size.x, size.y);
	}
	void GpuWindow::setSizeLimits(const IntVector2& min, const IntVector2& max)
	{
		if (min.x < 1 || min.y < 1 || max.x < 1 || max.y < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Size can not be less than one");
		}

		glfwSetWindowSizeLimits(window, min.x, min.y, max.x, max.y);
	}
	void GpuWindow::setPosition(const IntVector2& position)
	{
		glfwSetWindowPos(window, position.x, position.y);
	}
	void GpuWindow::setTitle(const std::string& title)
	{
		glfwSetWindowTitle(window, title.c_str());
	}
	void GpuWindow::setIcons(const std::vector<std::shared_ptr<ImageData>>& icons)
	{
#if INJECTOR_SYSTEM_WINDOWS
		auto images = std::vector<GLFWimage>(icons.size());

		for (size_t i = 0; i < icons.size(); i++)
		{
			auto& icon = icons[i];
			auto& image = images[i];
			image.width = icon->size.x;
			image.height = icon->size.y;
			image.pixels = icon->pixels.data();
		}
		
		glfwSetWindowIcon(
			window,
			static_cast<int>(images.size()),
			images.data());
#endif
	}
	void GpuWindow::setMouseMode(MouseMode mode)
	{
		glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
	}
	void GpuWindow::setMouseIcon(MouseIcon icon)
	{
		glfwSetCursor(window, nullptr);
		glfwDestroyCursor(cursor);

		cursor = glfwCreateStandardCursor(
			static_cast<int>(MouseIcon::Arrow));
		glfwSetCursor(window, cursor);
	}
	void GpuWindow::setMouseIcon(
		const std::shared_ptr<ImageData>& icon,
		const IntVector2& hotspot)
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
	void GpuWindow::setResizable(bool resizable)
	{
		glfwSetWindowAttrib(
			window,
			GLFW_RESIZABLE,
			resizable ? GLFW_TRUE : GLFW_FALSE);
	}
	void GpuWindow::setDecorated(bool decorated)
	{
		glfwSetWindowAttrib(
			window,
			GLFW_DECORATED,
			decorated ? GLFW_TRUE : GLFW_FALSE);
	}

	bool GpuWindow::isFocused() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
	}
	bool GpuWindow::isMinimized() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_TRUE;
	}
	bool GpuWindow::isVisible() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_VISIBLE) == GLFW_TRUE;
	}
	bool GpuWindow::isResizable() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_RESIZABLE) == GLFW_TRUE;
	}
	bool GpuWindow::isDecorated() const noexcept
	{
		return glfwGetWindowAttrib(window, GLFW_DECORATED) == GLFW_TRUE;
	}

	void GpuWindow::hide() noexcept
	{
		glfwHideWindow(window);
	}
	void GpuWindow::show() noexcept
	{
		glfwShowWindow(window);
	}
	void GpuWindow::minimize() noexcept
	{
		glfwIconifyWindow(window);
	}
	void GpuWindow::maximize() noexcept
	{
		glfwRestoreWindow(window);
	}
	void GpuWindow::focus() noexcept
	{
		glfwFocusWindow(window);
	}
	void GpuWindow::requestAttention() noexcept
	{
		glfwRequestWindowAttention(window);
	}

	std::shared_ptr<GpuMesh> GpuWindow::createMesh(
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
			vertexBuffer,
			indexBuffer);
	}

	std::shared_ptr<GpuImage> GpuWindow::createImage(
		GpuImageFormat format,
		int size,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return createImage(
			GpuImageType::Image1D,
			format,
			IntVector3(size, 1, 1),
			useMipmap,
			data);
	}
	std::shared_ptr<GpuImage> GpuWindow::createImage(
		GpuImageFormat format,
		const IntVector2& size,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return createImage(
			GpuImageType::Image2D,
			format,
			IntVector3(size, 1),
			useMipmap,
			data);
	}
	std::shared_ptr<GpuImage> GpuWindow::createImage(
		GpuImageFormat format,
		const IntVector3& size,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data)
	{
		return createImage(
			GpuImageType::Image3D,
			format,
			size,
			useMipmap,
			data);
	}

	std::shared_ptr<GpuPipeline> GpuWindow::createColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		return createColorPipeline(
			drawMode,
			vertexShader,
			fragmentShader,
			Vector4::one);
	}
	std::shared_ptr<GpuPipeline> GpuWindow::createColorColorPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		return createColorColorPipeline(
			drawMode,
			vertexShader,
			fragmentShader,
			Vector4::one);
	}
	std::shared_ptr<GpuPipeline> GpuWindow::createDiffusePipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader)
	{
		return createDiffusePipeline(
			drawMode,
			vertexShader,
			fragmentShader,
			Vector4::one,
			Vector4::one / 2.0f,
			Vector4::one,
			Vector3(1.0f, 2.0f, 3.0f).getNormalized());
	}
	std::shared_ptr<GpuPipeline> GpuWindow::createImageDiffusePipeline(
		GpuDrawMode drawMode,
		GpuImageFilter imageMinFilter,
		GpuImageFilter imageMagFilter,
		GpuImageFilter mipmapFilter,
		GpuImageWrap imageWrapU,
		GpuImageWrap imageWrapV,
		GpuImageWrap imageWrapW,
		const std::shared_ptr<GpuShader>& vertexShader,
		const std::shared_ptr<GpuShader>& fragmentShader,
		const std::shared_ptr<GpuImage>& image)
	{
		return createImageDiffusePipeline(
			drawMode,
			imageMinFilter,
			imageMagFilter,
			mipmapFilter,
			imageWrapU,
			imageWrapV,
			imageWrapW,
			vertexShader,
			fragmentShader,
			image,
			Vector4::one,
			Vector4::one / 2.0f,
			Vector4::one,
			Vector3(1.0f, 2.0f, 3.0f).getNormalized(),
			Vector2::one,
			Vector2::zero);
	}

	std::shared_ptr<GpuWindow> GpuWindow::create(
		const std::string& title,
		const IntVector2& size)
	{
		if(!Engine::isGraphicsInitialized())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Video is not initialized");
		}

		auto graphicsApi = Engine::getGraphicsAPI();

		if (graphicsApi == GraphicsAPI::OpenGL)
		{
			return Engine::createManager<GlGpuWindow>(
				false,
				title,
				size);
		}
		else if (graphicsApi == GraphicsAPI::OpenGLES)
		{
			return Engine::createManager<GlGpuWindow>(
				true,
				title,
				size);
		}
		else if (graphicsApi == GraphicsAPI::Vulkan)
		{
			return Engine::createManager<VkGpuWindow>(
				title,
				size);
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unknown graphics API");
		}
	}
}