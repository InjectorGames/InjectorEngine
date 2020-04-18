#pragma once
#include <injector_engine/config.hpp>

#ifdef VULKAN_FOUND
#define VULKAN_HPP_TYPESAFE_CONVERSION 1
#include <vulkan/vulkan.hpp>
#endif // VULKAN_FOUND

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

using namespace entityx;

namespace InjectorEngine
{
	enum class DebugLevel
	{
		Full,
		Trace,
		Info,
		Warn,
		Error,
		Fatal,
		Off,
	};

	enum class ShaderType
	{
		Vertex,
		TessellationControl,
		TessellationEvaluation,
		Geometry,
		Fragment,
		Compute,

		Raygen,
		AnyHit,
		ClosestHit,
		Miss,
		Intersection,
		Callable,
	};

	enum class CameraType
	{
		Perspective,
		Orthographic,
	};

	class Window
	{
	protected:
		std::string title;
		glm::ivec2 size;
		glm::ivec2 framebufferSize;

		GLFWwindow* window;
		EventManager* events;
		EntityManager* entities;
		SystemManager* systems;
	public:
		Window(std::string _title = "Injector Engine - Editor", glm::ivec2 _size = glm::ivec2(800, 600)) :
			title(_title),
			size(_size),
			framebufferSize(glm::ivec2(0)),
			window(nullptr)
		{
			events = new EventManager();
			entities = new EntityManager(*events);
			systems = new SystemManager(*entities, *events);
		}
		~Window()
		{
			delete systems;
			delete entities;
			delete events;

			if (window)
			{
				glfwDestroyWindow(window);
				window = nullptr;
			}
		}

		GLFWwindow* GetWindow() const
		{
			return window;
		}
		virtual void OnUpdate(double deltaTime)
		{
			systems->update_all(deltaTime);
		}

		const std::string& GetTitle() const
		{
			return title;
		}
		virtual void SetTitle(std::string _title)
		{
			glfwSetWindowTitle(window, _title.c_str());
			title = _title;
		}

		const glm::ivec2& GetSize() const
		{
			return size;
		}
		virtual void SetSize(glm::ivec2 _size)
		{
			glfwSetWindowSize(window, _size.x, _size.y);
			size = _size;
		}
		virtual void OnWindowResize(glm::ivec2 _size)
		{
			size = _size;
		}

		const glm::ivec2& GetFramebufferSize() const
		{
			return framebufferSize;
		}
		virtual void OnFramebufferResize(glm::ivec2 _size)
		{
			framebufferSize = size;
		}

		EventManager* GetEvents() const
		{
			return events;
		}
		EntityManager* GetEntities() const
		{
			return entities;
		}
		SystemManager* GetSystems() const
		{
			return systems;
		}
	};

	class Shader
	{
	public:
		const ShaderType type;
		Shader(ShaderType _type) : type(_type) {}
	};

	class Engine
	{
	private:
		inline static bool isInitialized = false;
		inline static DebugLevel debugLevel = DebugLevel::Full;

		inline static double time = 0;
		inline static double lastTime = 0;
		inline static double deltaTime = 0;

		inline static std::set<Window*> windows = {};

		static void ErrorCallback(int error, const char* description)
		{
			std::cerr << "GLFW error: Code = " << error << ", Description = " << description << ".\n";
		}
		static void WindowSizeCallback(GLFWwindow* window, int width, int height)
		{
			auto size = glm::ivec2(width, height);
			for (const auto& window : windows)
				window->OnWindowResize(size);
		}
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			auto size = glm::ivec2(width, height);
			for (const auto& window : windows)
				window->OnFramebufferResize(size);
		}
	public:
		inline static const std::string Name = "Injector Engine";

		static bool IsInitialized()
		{
			return isInitialized;
		}
		static void Initialize(DebugLevel _debugLevel = DebugLevel::Warn)
		{
			if (isInitialized)
				throw std::runtime_error("Failed to initialize engine: Engine is not terminated.");

			debugLevel = _debugLevel;

			std::cout << "Injector Engine version: " << INJECTOR_ENGINE_VERSION_MAJOR << "." << INJECTOR_ENGINE_VERSION_MINOR << "." << INJECTOR_ENGINE_VERSION_PATCH << std::endl;

			glfwSetErrorCallback(ErrorCallback);

			if (!glfwInit())
				throw std::runtime_error("Failed to intialize GLFW.");

			isInitialized = true;
		}
		static void Terminate()
		{
			if (!isInitialized)
				throw std::runtime_error("Failed to terminate engine: Engine is not initialized.");

			glfwTerminate();
			isInitialized = false;
		}
		static void Update()
		{
			int endUpdate = 0;

			while (endUpdate != windows.size())
			{
				time = glfwGetTime();
				deltaTime = time - lastTime;

				for (const auto& window : windows)
				{
					endUpdate += glfwWindowShouldClose(window->GetWindow());
					window->OnUpdate(deltaTime);
				}

				lastTime = time;
				glfwPollEvents();
			}
		}

		static DebugLevel GetDebugLevel()
		{
			return debugLevel;
		}
		static bool IsDebugEnabled()
		{
			return debugLevel != DebugLevel::Off;
		}

		static double GetTime()
		{
			return time;
		}
		static double GetLastTime()
		{
			return lastTime;
		}
		static double GetDeltaTime()
		{
			return deltaTime;
		}

		static void AddWindow(Window* window)
		{
			if (!windows.emplace(window).second)
				throw std::runtime_error("Failed to add engine window.");

			auto _window = window->GetWindow();
			glfwSetWindowSizeCallback(_window, WindowSizeCallback);
			glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
		}
		static void RemoveWindow(Window* window)
		{
			if (!windows.erase(window))
				throw std::runtime_error("Failed to remove engine window.");
		}

		static std::string ReadTextFromFile(const std::string& filePath)
		{
			std::ifstream ifs(filePath, std::ios::ate);

			if (!ifs)
				throw std::runtime_error("Failed to open text file.");

			size_t size = ifs.tellg();
			std::string buffer(size, ' ');

			ifs.seekg(0, std::ios::beg);
			ifs.read(&buffer[0], size);
			return buffer;
		}
		static std::vector<uint8_t> ReadBytesFromFile(const std::string& filePath)
		{
			std::ifstream ifs(filePath, std::ios::ate | std::ios::binary);

			if (!ifs)
				throw std::runtime_error("Failed to open binary file.");

			auto pos = ifs.tellg();
			std::vector<uint8_t> buffer(pos);

			ifs.seekg(0, std::ios::beg);
			ifs.read((char*)&buffer[0], pos);
			return buffer;
		}
	};

	struct TransformComponent : public Component<TransformComponent>
	{
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool isMatrixDirty;

		TransformComponent(glm::vec3 _scale = glm::vec3(1.0f), glm::vec3 _position = glm::vec3(0.0f), glm::quat _rotation = glm::quat(glm::vec3(0.0f)), glm::mat4 _matrix = glm::mat4(1.0f), bool _isMatrixDirty = true) :
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			isMatrixDirty(_isMatrixDirty)
		{}
	};

	struct TranslateComponent : public Component<TranslateComponent>
	{
		glm::vec3 translation;

		TranslateComponent(glm::vec3 _translation = glm::vec3(0.0f)) :
			translation(_translation)
		{}
	};
	struct RotateComponent : public Component<RotateComponent>
	{
		glm::quat rotation;

		RotateComponent(glm::quat _rotation = glm::quat(glm::vec3(0.0f))) :
			rotation(_rotation)
		{}
	};

	struct CameraComponent : public Component<CameraComponent>
	{
		CameraType type;
		int renderQueue;
		float fieldOfView;
		float aspectRatio;
		glm::vec4 frustum;
		glm::vec2 clipPlane;
		glm::mat4 matrix;
		bool isMatrixDirty;

		CameraComponent(CameraType _type = CameraType::Perspective, int _renderQueue = 0, float _fieldOfView = glm::radians(60.0f), float _aspectRatio = 4.0f / 3.0f, glm::vec4 _frustum = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f), glm::vec2 _clipPlane = glm::vec2(0.01f, 1000.0f), glm::mat4 _matrix = glm::mat4(1.0f), bool _isMatrixDirty = true) :
			type(_type),
			renderQueue(_renderQueue),
			fieldOfView(_fieldOfView),
			aspectRatio(_aspectRatio),
			frustum(_frustum),
			clipPlane(_clipPlane),
			matrix(_matrix),
			isMatrixDirty(_isMatrixDirty)
		{}
	};

	class TransformSystem : public System<TransformSystem>
	{
	public:
		void update(EntityManager& entities, EventManager& events, TimeDelta deltaTime) override
		{
			ComponentHandle<TransformComponent> transformComponent;
			ComponentHandle<TranslateComponent> translateComponent;
			ComponentHandle<RotateComponent> rotateComponent;

			// TODO: paralelize this

			for (auto entity : entities.entities_with_components(transformComponent))
			{
				if (entity.has_component<TranslateComponent>())
				{
					translateComponent = entity.component<TranslateComponent>();
					transformComponent->position += translateComponent->translation;
					transformComponent->isMatrixDirty = true;
				}

				if (entity.has_component<RotateComponent>())
				{
					rotateComponent = entity.component<RotateComponent>();
					transformComponent->rotation = transformComponent->rotation * rotateComponent->rotation;
					transformComponent->isMatrixDirty = true;
				}

				if (transformComponent->isMatrixDirty)
				{
					//matrix = glm::translate(oneMatrix, position) * glm::scale(oneMatrix, scale) * glm::mat4_cast(glm::normalize(rotation));
					transformComponent->matrix = glm::translate(glm::scale(glm::mat4_cast(glm::normalize(transformComponent->rotation)), transformComponent->scale), transformComponent->position);
					transformComponent->isMatrixDirty = false;
				}
			}
		}
	};

	class CameraSystem : public System<CameraSystem>
	{
	public:
		void update(EntityManager& entities, EventManager& events, TimeDelta deltaTime) override
		{
			ComponentHandle<CameraComponent> cameraComponent;

			// TODO: paralelize this

			for (auto entity : entities.entities_with_components(cameraComponent))
			{
				if (cameraComponent->isMatrixDirty)
				{
					if (cameraComponent->type == CameraType::Perspective)
					{
						cameraComponent->matrix = glm::perspective(cameraComponent->fieldOfView, cameraComponent->aspectRatio,
							cameraComponent->clipPlane.x, cameraComponent->clipPlane.y);
					}
					else if (cameraComponent->type == CameraType::Orthographic)
					{
						cameraComponent->matrix = glm::ortho(cameraComponent->frustum.x, cameraComponent->frustum.y, cameraComponent->frustum.z, cameraComponent->frustum.w,
							cameraComponent->clipPlane.x, cameraComponent->clipPlane.y);
					}
					else
					{
						throw std::runtime_error("Failed to update camera: unsupported type.");
					}

					cameraComponent->isMatrixDirty = false;
				}
			}
		}
	};
}
