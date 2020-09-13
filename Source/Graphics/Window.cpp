#include "Injector/Graphics/Window.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/NotImplementedException.hpp"
#include "Injector/Graphics/Primitive.hpp"
#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/VkWindow.hpp"


#include "SDL_events.h"

namespace Injector
{
	const std::string Window::defaultTitle = "Injector Engine";
	const IntVector2 Window::defaultPosition = IntVector2(
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	const IntVector2 Window::defaultSize = IntVector2(800, 600);
	const uint32_t Window::defaultFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;

	Window::Window(
		const std::string& title,
		IntVector2 position,
		IntVector2 size,
		uint32_t flags) :
		translation(),
		rotation(),
		mouseMotion()
	{
		window = SDL_CreateWindow(title.c_str(),
			position.x, position.y, size.x, size.y, flags);

		if (!window)
		{
			throw Exception("Window", "Window",
				"Failed to create SDL window, " + std::string(SDL_GetError()));
		}

		SDL_SetWindowMinimumSize(window, 1, 1);
	}
	Window::~Window()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	const Vector3& Window::getTranslation() const noexcept
	{
		return translation;
	}
	const Vector3& Window::getRotation() const noexcept
	{
		return rotation;
	}
	const IntVector2& Window::getMouseMotion() const noexcept
	{
		return mouseMotion;
	}

	void Window::update()
	{
		SDL_Event event;

		mouseMotion = IntVector2::zero;

		while (SDL_PollEvent(&event) != 0)
		{
			auto windowID = getID();

			if (event.type == SDL_WINDOWEVENT && event.window.windowID == windowID)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					onResize(IntVector2(event.window.data1, event.window.data2));
					break;
				case SDL_WINDOWEVENT_CLOSE:
					active = false;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION && event.motion.windowID == windowID)
			{
				mouseMotion += IntVector2(event.motion.xrel, event.motion.yrel);
			}
			else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.windowID == windowID)
			{
				if (event.key.keysym.sym == SDLK_a)
				{
					if (event.key.state == SDL_PRESSED)
						translation.x = -1.0f;
					else
						translation.x = 0.0f;
				}
				else if (event.key.keysym.sym == SDLK_d)
				{
					if (event.key.state == SDL_PRESSED)
						translation.x = 1.0f;
					else
						translation.x = 0.0f;
				}
				else if (event.key.keysym.sym == SDLK_LCTRL)
				{
					if (event.key.state == SDL_PRESSED)
						translation.y = -1.0f;
					else
						translation.y = 0.0f;
				}
				else if (event.key.keysym.sym == SDLK_SPACE)
				{
					if (event.key.state == SDL_PRESSED)
						translation.y = 1.0f;
					else
						translation.y = 0.0f;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					if (event.key.state == SDL_PRESSED)
						translation.z = -1.0f;
					else
						translation.z = 0.0f;
				}
				else if (event.key.keysym.sym == SDLK_w)
				{
					if (event.key.state == SDL_PRESSED)
						translation.z = 1.0f;
					else
						translation.z = 0.0f;
				}
			}
			/*
			// TODO: add mouse fire
			else if ((event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) && event.button.windowID == id)
			{
				events.emit<MouseButtonEvent>(event.button);
			}*/
		}

		rotation = Vector3(mouseMotion.y, mouseMotion.x, 0.0f);

		if(!isMinimized())
			Manager::update();
	}
	void Window::onResize(IntVector2 size)
	{
		throw NotImplementedException("Window", "onResize");
	}

	uint32_t Window::getID() const noexcept
	{
		return SDL_GetWindowID(window);
	}
	uint32_t Window::getFlags() const noexcept
	{
		return SDL_GetWindowFlags(window);
	}
	IntVector2 Window::getSize() const noexcept
	{
		auto size = IntVector2();
		SDL_GetWindowSize(window, &size.x, &size.y);
		return size;
	}
	IntVector2 Window::getMousePosition() const noexcept
	{
		auto position = IntVector2();
		SDL_GetMouseState(&position.x, &position.y);
		return position;
	}
	IntVector2 Window::getGlobalMousePosition() const noexcept
	{
		auto position = IntVector2();
		SDL_GetGlobalMouseState(&position.x, &position.y);
		return position;
	}
	uint32_t Window::getMouseButtons() const noexcept
	{
		return static_cast<uint32_t>(SDL_GetMouseState(nullptr, nullptr));
	}
	uint32_t Window::getGlobalMouseButtons() const noexcept
	{
		return static_cast<uint32_t>(SDL_GetGlobalMouseState(nullptr, nullptr));
	}
	void Window::getMouseState(IntVector2& position, uint32_t& buttons) const noexcept
	{
		buttons = static_cast<uint32_t>(SDL_GetMouseState(&position.x, &position.y));
	}
	void Window::getGlobalMouseState(IntVector2& position, uint32_t& buttons) const noexcept
	{
		buttons = static_cast<uint32_t>(SDL_GetGlobalMouseState(&position.x, &position.y));
	}
	bool Window::isHidden() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_HIDDEN;
	}
	bool Window::isShown() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
	}
	bool Window::isMinimized() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED;
	}
	bool Window::isMaximized() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED;
	}
	bool Window::isResizable() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
	}

	void Window::hide() noexcept
	{
		SDL_HideWindow(window);
	}
	void Window::show() noexcept
	{
		SDL_ShowWindow(window);
	}
	void Window::minimize() noexcept
	{
		SDL_MinimizeWindow(window);
	}
	void Window::maximize() noexcept
	{
		SDL_MaximizeWindow(window);
	}
	void Window::setResizable(bool resizable) noexcept
	{
		SDL_SetWindowResizable(window, static_cast<SDL_bool>(resizable));
	}
	bool Window::setMouseMode(bool realtive) noexcept
	{
		return SDL_SetRelativeMouseMode(static_cast<SDL_bool>(realtive)) == 0;
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
		TextureType type,
        IntVector3 size,
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
			Primitive::squareIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVN(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::squareVertices.size() * 3 +
			Primitive::squareNormals.size() * 3);

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
			Primitive::squareIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVT(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::squareVertices.size() * 3 +
			Primitive::squareTexCoords.size() * 2);

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
			Primitive::squareIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::squareIndices.data());

		return createMesh(
			Primitive::squareIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createSquareMeshVNT(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::squareVertices.size() * 3 +
			Primitive::squareNormals.size() * 3 +
			Primitive::squareTexCoords.size() * 2);

		for (size_t i = 0, j = 0; i < Primitive::squareVertices.size(); i++, j += 8)
		{
			memcpy(&vertices[j], &Primitive::squareVertices[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::squareNormals[i], sizeof(Vector3));
			memcpy(&vertices[j + 3], &Primitive::squareTexCoords[i], sizeof(Vector2));
		}

		auto vertexBuffer = createBuffer(
			vertices.size() * sizeof(float),
			BufferType::Vertex, mappable,
			vertices.data());
		auto indexBuffer = createBuffer(
			Primitive::squareIndices.size() * sizeof(Vector3),
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
			Primitive::cubeIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVN(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::cubeVertices.size() * 3 + 
			Primitive::cubeNormals.size() * 3);

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
			Primitive::cubeIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVT(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::cubeVertices.size() * 3 + 
			Primitive::cubeTexCoords.size() * 2);

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
			Primitive::cubeIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Mesh> Window::createCubeMeshVNT(bool mappable)
	{
		auto vertices = std::vector<float>(
			Primitive::cubeVertices.size() * 3 + 
			Primitive::cubeNormals.size() * 3 +
			Primitive::cubeTexCoords.size() * 2);

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
			Primitive::cubeIndices.size() * sizeof(Vector3),
			BufferType::Index, mappable,
			Primitive::cubeIndices.data());

		return createMesh(
			Primitive::cubeIndices.size(),
			BufferIndex::UnsignedShort,
			vertexBuffer, indexBuffer);
	}

	std::shared_ptr<Window> Window::create(
		const std::string& title,
		IntVector2 position,
		IntVector2 size,
		uint32_t flags)
	{
		auto graphicsApi = Engine::getGraphicsApi();

		if (graphicsApi == GraphicsApi::OpenGL)
			return Engine::createManager<GlWindow>(false, title, position, size, flags);
		else if (graphicsApi == GraphicsApi::OpenGLES)
			return Engine::createManager<GlWindow>(true, title, position, size, flags);
		else if (graphicsApi == GraphicsApi::Vulkan)
			return Engine::createManager<VkWindow>(title, position, size, flags);
		else
			throw Exception("Window", "createWindow", "Unknown graphics API");
	}
}