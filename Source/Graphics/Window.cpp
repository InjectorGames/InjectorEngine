#include "Injector/Graphics/Window.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/NotImplementedException.hpp"
#include "Injector/Graphics/Primitive.hpp"
#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/VkWindow.hpp"

namespace Injector
{
	const std::string Window::defaultTitle = "Injector Engine";
	const IntVector2 Window::defaultSize = IntVector2(800, 600);

	void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
		instance->deltaScroll = Vector2(static_cast<float>(xoffset), static_cast<float>(yoffset));
	}
	void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
		instance->isResized = true;
	}

	Window::Window(GLFWwindow* _window) :
		window(_window),
		deltaScroll(),
		isResized()
	{
		if (!window)
			throw NullException("Window", "Window", "window");

		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeLimits(window, 1, 1, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetScrollCallback(window, scrollCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		if (glfwRawMouseMotionSupported() == GLFW_TRUE)
    		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
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
		if(!glfwWindowShouldClose(window))
		{
			if(isResized)
			{
				auto size = getFramebufferSize();
				onFramebufferResize(size);
				isResized = false;
			}

			if(!isMinimized())
				Manager::update();

			active = true;
		}
		else
		{
			active = false;
		}
	}
	void Window::onFramebufferResize(const IntVector2& size)
	{
		throw NotImplementedException("Window", "onResize");
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

	void Window::setSize(const IntVector2& size)
	{
		glfwSetWindowSize(window, size.x, size.y);
	}
	void Window::setSizeLimits(const IntVector2& min, const IntVector2& max)
	{
		if(min.x < 1 || min.y < 1 || max.x < 1 || max.y < 1)
			throw Exception("Window", "setSizeLimits", "Size can not be less than one");

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
	void Window::setIcons(const std::vector<std::shared_ptr<Image>>& icons)
	{
		GLFWimage glfwIncons[icons.size()];

		for (size_t i = 0; i < icons.size(); i++)
		{
			auto& icon = icons[i];
			auto& glflwIcon = glfwIncons[i];
			auto& size = icon->getSize();
			glflwIcon.width = size.x;
			glflwIcon.height = size.y;
			glflwIcon.pixels = icon->getData();
		}
		
		glfwSetWindowIcon(window, icons.size(), glfwIncons);
	}
	void Window::setMouseMode(MouseMode mode)
	{
		glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
	}
	void Window::setResizable(bool resizable)
	{
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	}
	void Window::setDecorated(bool decorated)
	{
		glfwSetWindowAttrib(window, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
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
		throw NotImplementedException("Window", "createCameraSystem");
	}
	std::shared_ptr<RenderSystem> Window::createRenderSystem()
	{
		throw NotImplementedException("Window", "createRenderSystem");
	}

	std::shared_ptr<Buffer> Window::createBuffer(
		size_t size,
		BufferType type,
		bool mappable,
		const void* data)
	{
		throw NotImplementedException("Window", "createBuffer");
	}
	std::shared_ptr<Mesh> Window::createMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer)
	{
		throw NotImplementedException("Window", "createMesh");
	}
	std::shared_ptr<Texture> Window::createTexture(
        int size,
        TextureFormat format,
        TextureFilter minFilter,
    	TextureFilter magFilter,
    	TextureWrap wrapU,
        bool useMipmap,
		const std::shared_ptr<Image>& image)
	{
		throw NotImplementedException("Window", "createTexture");
	}
	std::shared_ptr<Texture> Window::createTexture(
        const IntVector2& size,
        TextureFormat format,
        TextureFilter minFilter,
    	TextureFilter magFilter,
    	TextureWrap wrapU,
		TextureWrap wrapV,
        bool useMipmap,
		const std::shared_ptr<Image>& image)
	{
		throw NotImplementedException("Window", "createTexture");
	}
	std::shared_ptr<Texture> Window::createTexture(
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
		throw NotImplementedException("Window", "createTexture");
	}

	std::shared_ptr<ColorPipeline> Window::createColorPipeline()
	{
		throw NotImplementedException("Window", "createColorPipeline");
	}
	std::shared_ptr<ColorPipeline> Window::createColColorPipeline()
	{
		throw NotImplementedException("Window", "createColColorPipeline");
	}
	std::shared_ptr<DiffusePipeline> Window::createDiffusePipeline()
	{
		throw NotImplementedException("Window", "createDiffusePipeline");
	}
	std::shared_ptr<TexDiffusePipeline> Window::createTexDiffusePipeline(
		const std::shared_ptr<Texture>& texture)
	{
		throw NotImplementedException("Window", "createTexDiffusePipeline");
	}

	std::shared_ptr<Mesh> Window::createSquareMeshV(bool mappable)
	{
		auto vertexBuffer = createBuffer(
			Primitive::squareVertices.size() * sizeof(Vector3),
			BufferType::Vertex, mappable,
			Primitive::squareVertices.data());
		auto indexBuffer = createBuffer(
			Primitive::squareIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVN(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::squareVertices.size() * 6);

		for (size_t i = 0, j = 0; i < Primitive::squareVertices.size(); i++, j += 6)
		{
			memcpy(&vertices[j], &Primitive::squareVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::squareNormals[i], sizeof(Vector3));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::squareIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVT(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::squareVertices.size() * 5);

		for (size_t i = 0, j = 0; i < Primitive::squareVertices.size(); i++, j += 5)
		{
			memcpy(&vertices[j], &Primitive::squareVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::squareTexCoords[i], sizeof(Vector2));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::squareIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVNT(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::squareVertices.size() * 8);

		for (size_t i = 0, j = 0; i < Primitive::squareVertices.size(); i++, j += 8)
		{
			memcpy(&vertices[j], &Primitive::squareVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::squareNormals[i], sizeof(Vector3));
			memcpy(&vertices[j + 6], &Primitive::squareTexCoords[i], sizeof(Vector2));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::squareIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshV(bool mappable)
	{
		auto vertexBuffer = createBuffer(
			Primitive::cubeVertices.size() * sizeof(Vector3),
			BufferType::Vertex, mappable,
			Primitive::cubeVertices.data());
		auto indexBuffer = createBuffer(
			Primitive::cubeIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVN(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::cubeVertices.size() * 6);

		for (size_t i = 0, j = 0; i < Primitive::cubeVertices.size(); i++, j += 6)
		{
			memcpy(&vertices[j], &Primitive::cubeVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::cubeNormals[i], sizeof(Vector3));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::cubeIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVT(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::cubeVertices.size() * 5);

		for (size_t i = 0, j = 0; i < Primitive::cubeVertices.size(); i++, j += 5)
		{
			memcpy(&vertices[j], &Primitive::cubeVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::cubeTexCoords[i], sizeof(Vector2));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::cubeIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVNT(bool mappable)
	{
		auto vertices = std::vector<float>(Primitive::cubeVertices.size() * 8);

		for (size_t i = 0, j = 0; i < Primitive::cubeVertices.size(); i++, j += 8)
		{
			memcpy(&vertices[j], &Primitive::cubeVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::cubeNormals[i], sizeof(Vector3));
			memcpy(&vertices[j + 6], &Primitive::cubeTexCoords[i], sizeof(Vector2));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::cubeIndices.size() * sizeof(uint16_t),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}

	std::shared_ptr<Window> Window::create(
		const std::string& title,
		const IntVector2& size)
	{
		auto graphicsApi = Engine::getGraphicsApi();

		if (graphicsApi == GraphicsApi::OpenGL)
			return Engine::createManager<GlWindow>(false, title, size);
		else if (graphicsApi == GraphicsApi::OpenGLES)
			return Engine::createManager<GlWindow>(true, title, size);
		else if (graphicsApi == GraphicsApi::Vulkan)
			return Engine::createManager<VkWindow>(title, size);
		else
			throw Exception("Window", "createWindow", "Unknown graphics API");
	}
}