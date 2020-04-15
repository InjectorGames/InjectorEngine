#pragma once
#include <injector_engine/config.hpp>

#ifdef VULKAN_FOUND
#define VULKAN_HPP_TYPESAFE_CONVERSION 1
#include <vulkan/vulkan.hpp>
#endif // VULKAN_FOUND

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <entityx/entityx.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
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

namespace InjectorEngine
{
	class Engine;
	class System;
	class Window;

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

	struct Transform
	{
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool isMatrixChanged;
	};

	struct Camera
	{
		float fieldOfView;
		float aspectRatio;
		float nearClipPlane;
		float farClipPlane;

		glm::mat4 projMatrix;
		glm::mat4 viewProjMatrix;
		bool isProjMatrixChanged;
		bool isViewProjMatrixChanged;
	};

	class Engine
	{
	public:
		enum class DebugLevelType
		{
			Full,
			Trace,
			Info,
			Warn,
			Error,
			Fatal,
			Off,
		};
	private:
		static bool isInitialized;
		static DebugLevelType debugLevel;
		static std::set<Window*> windows;

		static void ErrorCallback(int error, const char* description);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

		static bool CompareSystem(const std::shared_ptr<System>& a, const std::shared_ptr<System>& b);
	public:
		static const std::string Name;

		static bool IsInitialized();
		static void Initialize(DebugLevelType debugLevel = DebugLevelType::Warn);
		static void Terminate();
		static void Update();

		static DebugLevelType GetDebugLevel();
		static bool IsDebugEnabled();

		static void AddWindow(Window* window);
		static void RemoveWindow(Window* window);

		static std::string ReadTextFromFile(const std::string& filePath);
		static std::vector<uint8_t> ReadBytesFromFile(const std::string& filePath);
	};

	class Shader
	{
	public:
		const ShaderType type;
		Shader(ShaderType type);
	};

	class System
	{
	public:
		struct Comparator
		{
			bool operator()(const System& a, const System& b) const;
			bool operator()(const System* a, const System* b) const;
		};

		const int updateQueue;
		System(int updateQueue);

		virtual void OnUpdateBegin(Window* window);
		virtual void OnUpdate(Window* window);
		virtual void OnUpdateEnd(Window* window);
	};

	class Window
	{
	protected:
		GLFWwindow* window;
		//entt::registry registry;

		std::string title;
		glm::ivec2 size;
		glm::ivec2 framebufferSize;

		std::set<System*, System::Comparator> systems;
	public:
		Window(std::string title = "Injector Engine - Editor", glm::ivec2 size = glm::ivec2(800, 600));
		~Window();

		GLFWwindow* GetWindow() const;
		//entt::registry& GetRegistry();

		const std::string& GetTitle() const;
		virtual void SetTitle(std::string title);

		const glm::ivec2& GetSize() const;
		virtual void SetSize(glm::ivec2 size);
		virtual void OnWindowResize(glm::ivec2 size);

		const glm::ivec2& GetFramebufferSize() const;
		virtual void OnFramebufferResize(glm::ivec2 size);

		virtual void AddSystem(System* system);
		virtual void RemoveSystem(System* system);

		virtual void OnUpdateBegin();
		virtual void OnUpdate();
		virtual void OnUpdateEnd();
	};
}
