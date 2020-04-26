#pragma once
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <dear-imgui/imgui.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if USE_WAYLAND
#		include <wayland-egl.h>
#		define GLFW_EXPOSE_NATIVE_WAYLAND
#	else
#		define GLFW_EXPOSE_NATIVE_X11
#		define GLFW_EXPOSE_NATIVE_GLX
#	endif
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif
#include <GLFW/glfw3native.h>

#include <set>
#include <vector>
#include <iostream>

namespace njng
{
	static GLFWwindow* window = nullptr;

	static void ErrorCallback(int error, const char* description)
	{
		std::cerr << "GLFW error: Code = " << error << ", Description = " << description << ".\n";
	}

	static void Initialize()
	{
		std::cout << "Injector Engine version: " <<
			NJNG_VERSION_MAJOR << "." <<
			NJNG_VERSION_MINOR << "." <<
			NJNG_VERSION_PATCH << std::endl;

		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
			throw std::runtime_error("Failed to intialize GLFW.");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(800, 600, "NJNG Test", nullptr, nullptr);

		bgfx::PlatformData pd = {};
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if USE_WAYLAND
		pd.ndt = glfwGetWaylandDisplay();
#	else
		pd.ndt = glfwGetX11Display();
#	endif
#endif
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if USE_WAYLAND
		wl_egl_window* win_impl = (wl_egl_window*)glfwGetWindowUserPointer(window);
		if (!win_impl)
		{
			int width, height;
			glfwGetWindowSize(_window, &width, &height);
			struct wl_surface* surface = (struct wl_surface*)glfwGetWaylandWindow(window);
			if (surface)
			{
				win_impl = wl_egl_window_create(surface, width, height);
				glfwSetWindowUserPointer(window, (void*)(uintptr_t)win_impl);
			}
		}
		pd.nwh = (void*)(uintptr_t)win_impl;
#	else
		pd.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#	endif
#elif BX_PLATFORM_OSX
		pd.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
		pd.nwh = glfwGetWin32Window(window);
#endif
		bgfx::setPlatformData(pd);

		bgfx::Init bgfxInit = {};
		bgfxInit.type = bgfx::RendererType::Direct3D12;
		bgfxInit.resolution.width = 800;
		bgfxInit.resolution.height = 600;
		bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

		if (!bgfx::init(bgfxInit))
			throw std::runtime_error("Failed to intialize BGFX.");

		bgfx::setDebug(BGFX_DEBUG_TEXT);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	}
	static void Terminate()
	{
		bgfx::shutdown();

		if (window)
		{
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if USE_WAYLAND
			wl_egl_window* win_impl = (wl_egl_window*)glfwGetWindowUserPointer(window);
			if (win_impl)
			{
				glfwSetWindowUserPointer(window, nullptr);
				wl_egl_window_destroy(win_impl);
			}
#	endif
#endif
			glfwDestroyWindow(window);
			window = nullptr;
		}

		glfwTerminate();
	}
	static void BeginUpdate()
	{
		while (glfwWindowShouldClose(window) == GLFW_FALSE)
		{
			bgfx::setViewRect(0, 0, 0, 800, 600);
			bgfx::touch(0);
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x0f, "Test text");
			bgfx::frame();
			glfwPollEvents();
		}
	}
}

/*
#include <ngng/config.hpp>

#include <bgfx/bgfx.h>
#include <common/entry/entry.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entityx/entityx.h>
#include <FastNoiseSIMD/FastNoiseSIMD.h>
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

namespace ecs = entityx;

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

	enum class CursorMode
	{
		Normal = GLFW_CURSOR_NORMAL,
		Disabled = GLFW_CURSOR_DISABLED,
		Hidden = GLFW_CURSOR_HIDDEN,
	};

	enum class KeyMod
	{
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,
		Super = GLFW_MOD_SUPER,
		CapsLock = GLFW_MOD_CAPS_LOCK,
		NumLock = GLFW_MOD_NUM_LOCK,
	};

	enum class KeyAction
	{
		Press = GLFW_PRESS,
		Repeat = GLFW_REPEAT,
		Release = GLFW_RELEASE,
	};

	enum class KeyType
	{
		Unknown = GLFW_KEY_UNKNOWN,
		Space = GLFW_KEY_SPACE,
		Apostrophe = GLFW_KEY_APOSTROPHE,
		Comma = GLFW_KEY_COMMA,
		Minus = GLFW_KEY_MINUS,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,
		_0 = GLFW_KEY_0,
		_1 = GLFW_KEY_1,
		_2 = GLFW_KEY_2,
		_3 = GLFW_KEY_3,
		_4 = GLFW_KEY_4,
		_5 = GLFW_KEY_5,
		_6 = GLFW_KEY_6,
		_7 = GLFW_KEY_7,
		_8 = GLFW_KEY_8,
		_9 = GLFW_KEY_9,
		Semicolon = GLFW_KEY_SEMICOLON,
		Equal = GLFW_KEY_EQUAL,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		Backslash = GLFW_KEY_BACKSLASH,
		RightBracket = GLFW_KEY_RIGHT_BRACKET,
		GraveAccent = GLFW_KEY_GRAVE_ACCENT,
		World1 = GLFW_KEY_WORLD_1,
		World2 = GLFW_KEY_WORLD_2,
		Escape = GLFW_KEY_ESCAPE,
		Enter = GLFW_KEY_ENTER,
		Tab = GLFW_KEY_TAB,
		Backspace = GLFW_KEY_BACKSPACE,
		Insert = GLFW_KEY_INSERT,
		Delete = GLFW_KEY_DELETE,
		Right = GLFW_KEY_RIGHT,
		Left = GLFW_KEY_LEFT,
		Down = GLFW_KEY_DOWN,
		Up = GLFW_KEY_UP,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,
		Home = GLFW_KEY_HOME,
		End = GLFW_KEY_END,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		ScrollLock = GLFW_KEY_SCROLL_LOCK,
		NumLock = GLFW_KEY_NUM_LOCK,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		Pause = GLFW_KEY_PAUSE,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
		Kp0 = GLFW_KEY_KP_0,
		Kp1 = GLFW_KEY_KP_1,
		Kp2 = GLFW_KEY_KP_2,
		Kp3 = GLFW_KEY_KP_3,
		Kp4 = GLFW_KEY_KP_4,
		Kp5 = GLFW_KEY_KP_5,
		Kp6 = GLFW_KEY_KP_6,
		Kp7 = GLFW_KEY_KP_7,
		Kp8 = GLFW_KEY_KP_8,
		Kp9 = GLFW_KEY_KP_9,
		KpDecimal = GLFW_KEY_KP_DECIMAL,
		KpDivide = GLFW_KEY_KP_DIVIDE,
		KpMultiply = GLFW_KEY_KP_MULTIPLY,
		KpSubtract = GLFW_KEY_KP_SUBTRACT,
		KpAdd = GLFW_KEY_KP_ADD,
		KpEnter = GLFW_KEY_KP_ENTER,
		KpEqual = GLFW_KEY_KP_EQUAL,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		LeftSuper = GLFW_KEY_LEFT_SUPER,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		RightSuper = GLFW_KEY_RIGHT_SUPER,
		Menu = GLFW_KEY_MENU,
		Last = GLFW_KEY_LAST,
	};

	enum class MouseButtonAction
	{
		Press = GLFW_PRESS,
		Release = GLFW_RELEASE,
	};

	enum class MouseButtonType
	{
		_1 = GLFW_MOUSE_BUTTON_1,
		_2 = GLFW_MOUSE_BUTTON_2,
		_3 = GLFW_MOUSE_BUTTON_3,
		_4 = GLFW_MOUSE_BUTTON_4,
		_5 = GLFW_MOUSE_BUTTON_5,
		_6 = GLFW_MOUSE_BUTTON_6,
		_7 = GLFW_MOUSE_BUTTON_7,
		_8 = GLFW_MOUSE_BUTTON_8,
		Last = GLFW_MOUSE_BUTTON_LAST,
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Right = GLFW_MOUSE_BUTTON_RIGHT,
		Middle = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	struct WindowSizeEvent final : public ecs::Event<WindowSizeEvent>
	{
		glm::ivec2 size;
		glm::ivec2 deltaSize;

		WindowSizeEvent(glm::ivec2 _size, glm::ivec2 _deltaSize) :
			size(_size),
			deltaSize(_deltaSize)
		{}
	};
	struct FramebufferSizeEvent final : public ecs::Event<FramebufferSizeEvent>
	{
		glm::ivec2 size;
		glm::ivec2 deltaSize;

		FramebufferSizeEvent(glm::ivec2 _size, glm::ivec2 _deltaSize) :
			size(_size),
			deltaSize(_deltaSize)
		{}
	};
	struct ContentScaleEvent final : public ecs::Event<ContentScaleEvent>
	{
		glm::vec2 scale;
		glm::vec2 deltaScale;

		ContentScaleEvent(glm::vec2 _scale, glm::vec2 _deltaScale) :
			scale(_scale),
			deltaScale(_deltaScale)
		{}
	};
	struct WindowPositionEvent final : public ecs::Event<WindowPositionEvent>
	{
		glm::ivec2 position;
		glm::ivec2 deltaPosition;

		WindowPositionEvent(glm::ivec2 _position, glm::ivec2 _deltaPosition) :
			position(_position),
			deltaPosition(_deltaPosition)
		{}
	};
	struct CursorPositionEvent final : public ecs::Event<CursorPositionEvent>
	{
		glm::dvec2 position;
		glm::dvec2 deltaPosition;

		CursorPositionEvent(const glm::dvec2& _position, const glm::dvec2& _deltaPosition) :
			position(_position),
			deltaPosition(_deltaPosition)
		{}
	};
	struct AspectRatioEvent final : public ecs::Event<AspectRatioEvent>
	{
		float_t aspectRatio;
		float_t deltaAspectRatio;

		AspectRatioEvent(float_t _aspectRatio, float_t _deltaAspectRatio) :
			aspectRatio(_aspectRatio),
			deltaAspectRatio(_deltaAspectRatio)
		{}
	};
	struct WindowCloseEvent final : public ecs::Event<WindowCloseEvent>
	{
		WindowCloseEvent()
		{}
	};
	struct WindowRefreshEvent final : public ecs::Event<WindowRefreshEvent>
	{
		WindowRefreshEvent()
		{}
	};
	struct WindowIconifyEvent final : public ecs::Event<WindowIconifyEvent>
	{
		bool iconified;

		WindowIconifyEvent(bool _iconified) :
			iconified(_iconified)
		{}
	};
	struct WindowMaximizeEvent final : public ecs::Event<WindowMaximizeEvent>
	{
		bool maximized;

		WindowMaximizeEvent(bool _maximized) :
			maximized(_maximized)
		{}
	};
	struct WindowFocusEvent final : public ecs::Event<WindowFocusEvent>
	{
		bool focused;

		WindowFocusEvent(bool _focused) :
			focused(_focused)
		{}
	};
	struct CursorEnterEvent final : public ecs::Event<CursorEnterEvent>
	{
		bool entered;

		CursorEnterEvent(bool _entered) :
			entered(_entered)
		{}
	};
	struct KeyEvent final : public ecs::Event<KeyEvent>
	{
		KeyType key;
		int32_t scancode;
		KeyAction action;
		int32_t mods;

		KeyEvent(KeyType _key, int32_t _scancode, KeyAction _action, int32_t _mods) :
			key(_key),
			scancode(_scancode),
			action(_action),
			mods(_mods)
		{}
	};
	struct CharacterEvent final : public ecs::Event<CharacterEvent>
	{
		uint32_t codepoint;

		CharacterEvent(uint32_t _codepoint) :
			codepoint(_codepoint)
		{}
	};
	struct MouseButtonEvent final : public ecs::Event<MouseButtonEvent>
	{
		MouseButtonType button;
		MouseButtonAction action;
		int32_t mods;

		MouseButtonEvent(MouseButtonType _button, MouseButtonAction _action, int32_t _mods) :
			button(_button),
			action(_action),
			mods(_mods)
		{}
	};
	struct ScrollEvent final : public ecs::Event<ScrollEvent>
	{
		glm::dvec2 offset;

		ScrollEvent(glm::dvec2 _offset) :
			offset(_offset)
		{}
	};

	struct TransformComponent final : public ecs::Component<TransformComponent>
	{
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool isMatrixChanged;

		TransformComponent(glm::vec3 _scale = glm::vec3(1.0f), glm::vec3 _position = glm::vec3(0.0f), glm::quat _rotation = glm::quat(glm::vec3(0.0f)), glm::mat4 _matrix = glm::mat4(1.0f), bool _isMatrixChanged = true) :
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			isMatrixChanged(_isMatrixChanged)
		{}
	};

	struct TranslateComponent final : public ecs::Component<TranslateComponent>
	{
		glm::vec3 translation;

		TranslateComponent(glm::vec3 _translation = glm::vec3(0.0f)) :
			translation(_translation)
		{}
	};
	struct RotateComponent final : public ecs::Component<RotateComponent>
	{
		glm::vec3 rotation;

		RotateComponent(glm::vec3 _rotation = glm::vec3(0.0f)) :
			rotation(_rotation)
		{}
	};

	struct CameraComponent final : public ecs::Component<CameraComponent>
	{
		CameraType type;
		int32_t renderQueue;
		float_t fieldOfView;
		float_t aspectRatio;
		bool updateAspectRatio;
		glm::vec4 frustum;
		glm::vec2 clipPlane;
		glm::mat4 matrix;
		bool isMatrixChanged;

		CameraComponent(CameraType _type = CameraType::Perspective, int32_t _renderQueue = 0, float_t _fieldOfView = glm::radians(60.0f), float_t _aspectRatio = 4.0f / 3.0f, bool _updateAspectRatio = true, glm::vec4 _frustum = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f), glm::vec2 _clipPlane = glm::vec2(0.01f, 1000.0f), glm::mat4 _matrix = glm::mat4(1.0f), bool _isMatrixChanged = true) :
			type(_type),
			renderQueue(_renderQueue),
			fieldOfView(_fieldOfView),
			aspectRatio(_aspectRatio),
			updateAspectRatio(_updateAspectRatio),
			frustum(_frustum),
			clipPlane(_clipPlane),
			matrix(_matrix),
			isMatrixChanged(_isMatrixChanged)
		{}
	};

	class Window
	{
	protected:
		std::string title;
		CursorMode cursorMode;
		glm::ivec2 windowSize;
		glm::ivec2 framebufferSize;
		glm::vec2 contentScale;
		glm::ivec2 windowPosition;
		glm::dvec2 cursorPosition;
		float_t aspectRatio;

		GLFWwindow* window;
		ecs::EventManager* events;
		ecs::EntityManager* entities;
		ecs::SystemManager* systems;
	public:
		Window(std::string _title = "Injector Engine - Editor", glm::ivec2 _size = glm::ivec2(800, 600)) :
			title(_title),
			cursorMode(CursorMode::Normal),
			windowSize(_size),
			framebufferSize(glm::ivec2(0)),
			contentScale(glm::vec2(0.0f)),
			windowPosition(glm::ivec2(0)),
			cursorPosition(glm::dvec2(0.0)),
			aspectRatio(float_t(_size.x) / float_t(_size.y)),
			window(nullptr)
		{
			events = new ecs::EventManager();
			entities = new ecs::EntityManager(*events);
			systems = new ecs::SystemManager(*entities, *events);
		}
		virtual ~Window()
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

		inline std::string GetTitle() const
		{
			return title;
		}
		virtual void SetTitle(std::string _title)
		{
			glfwSetWindowTitle(window, _title.c_str());
			title = _title;
		}

		inline CursorMode GetCursorMode() const
		{
			return cursorMode;
		}
		virtual void SetCursorMode(CursorMode _cursorMode)
		{
			glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(_cursorMode));
			cursorMode = _cursorMode;
		}

		inline glm::ivec2 GetWindowSize() const
		{
			return windowSize;
		}
		virtual void SetWindowSize(glm::ivec2 size)
		{
			glfwSetWindowSize(window, size.x, size.y);
			windowSize = size;
		}

		inline glm::ivec2 GetFramebufferSize() const
		{
			return framebufferSize;
		}
		inline glm::vec2 GetContentScale() const
		{
			return contentScale;
		}
		inline glm::ivec2 GetWindowPosition() const
		{
			return windowPosition;
		}
		inline glm::dvec2 GetCursorPosition() const
		{
			return cursorPosition;
		}
		inline float_t GetAspectRatio() const
		{
			return aspectRatio;
		}

		inline GLFWwindow* GetWindow() const
		{
			return window;
		}
		inline ecs::EventManager* GetEvents() const
		{
			return events;
		}
		inline ecs::EntityManager* GetEntities() const
		{
			return entities;
		}
		inline ecs::SystemManager* GetSystems() const
		{
			return systems;
		}

		virtual void OnUpdate(double_t deltaTime)
		{
			auto intVec2 = glm::ivec2();
			auto floatVec2 = glm::vec2();
			auto doubleVec2 = glm::dvec2();

			glfwGetWindowSize(window, &intVec2.x, &intVec2.y);
			if (windowSize != intVec2)
			{
				events->emit<WindowSizeEvent>(intVec2, intVec2 - windowSize);
				windowSize = intVec2;
			}

			glfwGetFramebufferSize(window, &intVec2.x, &intVec2.y);
			if (framebufferSize != intVec2)
			{
				events->emit<FramebufferSizeEvent>(intVec2, intVec2 - framebufferSize);
				framebufferSize = intVec2;

				auto _aspecetRatio = (float_t(intVec2.x) / float_t(intVec2.y));
				if (aspectRatio != _aspecetRatio)
				{
					events->emit<AspectRatioEvent>(_aspecetRatio, _aspecetRatio - aspectRatio);
					aspectRatio = _aspecetRatio;
				}
			}

			glfwGetWindowContentScale(window, &floatVec2.x, &floatVec2.y);
			if (contentScale != floatVec2)
			{
				events->emit<ContentScaleEvent>(floatVec2, floatVec2 - contentScale);
				contentScale = floatVec2;
			}

			glfwGetWindowPos(window, &intVec2.x, &intVec2.y);
			if (windowPosition != intVec2)
			{
				events->emit<WindowPositionEvent>(intVec2, intVec2 - windowPosition);
				windowPosition = intVec2;
			}
			
			glfwGetCursorPos(window, &doubleVec2.x, &doubleVec2.y);
			if (cursorPosition != doubleVec2)
			{
				events->emit<CursorPositionEvent>(doubleVec2, doubleVec2 - cursorPosition);
				cursorPosition = doubleVec2;
			}

			// TODO:
			//glfwGetMonitorContentScale
			//glfwGetMonitorPhysicalSize


			systems->update_all(static_cast<ecs::TimeDelta>(deltaTime));
		}

		virtual void OnWindowClose()
		{
			events->emit<WindowCloseEvent>();
		}
		virtual void OnWindowRefresh()
		{
			events->emit<WindowRefreshEvent>();
		}
		virtual void OnWindowIconify(bool iconified)
		{
			events->emit<WindowIconifyEvent>(iconified);
		}
		virtual void OnWindowMaximize(bool maximized)
		{
			events->emit<WindowMaximizeEvent>(maximized);
		}
		virtual void OnWindowFocus(bool focused)
		{
			events->emit<WindowFocusEvent>(focused);
		}
		virtual void OnCursorEnter(bool entered)
		{
			events->emit<CursorEnterEvent>(entered);
		}
		virtual void OnKey(KeyType key, int32_t scancode, KeyAction action, int32_t mods)
		{
			events->emit<KeyEvent>(key, scancode, action, mods);
		}
		virtual void OnCharacter(uint32_t codepoint)
		{
			events->emit<CharacterEvent>(codepoint);
		}
		virtual void OnMouseButton(MouseButtonType button, MouseButtonAction action, int32_t mods)
		{
			events->emit<MouseButtonEvent>(button, action, mods);
		}
		virtual void OnScroll(glm::dvec2 offset)
		{
			events->emit<ScrollEvent>(offset);
		}
	};

	class Shader
	{
	public:
		const ShaderType type;
		Shader(ShaderType _type) : type(_type)
		{}
	};

	class Engine final
	{
	private:
		inline static bool isInitialized = false;
		inline static DebugLevel debugLevel = DebugLevel::Full;

		inline static std::set<Window*> windows = {};

		static void ErrorCallback(int error, const char* description)
		{
			std::cerr << "GLFW error: Code = " << error << ", Description = " << description << ".\n";
		}
		static void WindowCloseCallback(GLFWwindow* window)
		{
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnWindowClose();
				return;
			}
		}
		static void WindowRefreshCallback(GLFWwindow* window)
		{
			//draw_editor_ui(window);
			//glfwSwapBuffers(window);

			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnWindowRefresh();
				return;
			}
		}
		static void WindowIconifyCallback(GLFWwindow* window, int iconified)
		{
			auto _iconified = iconified == GLFW_TRUE;
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnWindowIconify(_iconified);
				return;
			}
		}
		static void WindowMaximizeCallback(GLFWwindow* window, int maximized)
		{
			auto _maximized = maximized == GLFW_TRUE;
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnWindowMaximize(_maximized);
				return;
			}
		}
		static void WindowFocusCallback(GLFWwindow* window, int focused)
		{
			auto _focused = focused == GLFW_TRUE;
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnWindowFocus(_focused);
				return;
			}
		}
		static void CursorEnterCallback(GLFWwindow* window, int entered)
		{
			auto _entered = entered == GLFW_TRUE;
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnCursorEnter(_entered);
				return;
			}
		}
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnKey(static_cast<KeyType>(key), static_cast<int32_t>(scancode), static_cast<KeyAction>(action), static_cast<int32_t>(mods));
				return;
			}
		}
		static void CharacterCallback(GLFWwindow* window, unsigned int codepoint)
		{
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnCharacter(static_cast<uint32_t>(codepoint));
				return;
			}
		}
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnMouseButton(static_cast<MouseButtonType>(button), static_cast<MouseButtonAction>(action), static_cast<int32_t>(mods));
				return;
			}
		}
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			auto _offset = glm::dvec2(xoffset, yoffset);
			for (const auto _window : windows)
			{
				if (window != _window->GetWindow())
					continue;
				_window->OnScroll(_offset);
				return;
			}
		}
	public:
		inline static const std::string Name = "Injector Engine";

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

			for (const auto window : windows)
				delete window;

			windows.clear();

			glfwTerminate();
			isInitialized = false;
		}
		static void Update()
		{
			int32_t endUpdate = 0;
			double_t time = 0.0;

			while (endUpdate != windows.size())
			{
				auto currentTime = static_cast<double_t>(glfwGetTime());
				auto deltaTime = currentTime - time;

				for (const auto& window : windows)
				{
					endUpdate += static_cast<int32_t>(glfwWindowShouldClose(window->GetWindow()));
					window->OnUpdate(deltaTime);
				}

				time = currentTime;
				glfwPollEvents();
			}
		}

		inline static bool IsInitialized()
		{
			return isInitialized;
		}
		inline static DebugLevel GetDebugLevel()
		{
			return debugLevel;
		}
		inline static bool IsDebugEnabled()
		{
			return debugLevel != DebugLevel::Off;
		}

		template<typename TWindow, typename ... TArgs>
		static TWindow* InstantiateWindow(TArgs&& ... args)
		{
			auto window = new TWindow(args...);

			if (!windows.emplace(window).second)
				throw std::runtime_error("Failed to add engine window.");

			auto windowInstance = window->GetWindow();
			glfwSetWindowCloseCallback(windowInstance, WindowCloseCallback);
			glfwSetWindowRefreshCallback(windowInstance, WindowRefreshCallback);
			glfwSetWindowIconifyCallback(windowInstance, WindowIconifyCallback);
			glfwSetWindowMaximizeCallback(windowInstance, WindowMaximizeCallback);
			glfwSetWindowFocusCallback(windowInstance, WindowFocusCallback);
			glfwSetCursorEnterCallback(windowInstance, CursorEnterCallback);
			glfwSetKeyCallback(windowInstance, KeyCallback);
			glfwSetCharCallback(windowInstance, CharacterCallback);
			glfwSetMouseButtonCallback(windowInstance, MouseButtonCallback);
			glfwSetScrollCallback(windowInstance, ScrollCallback);

			// TODO: Add joystick/gamepad input, Add cursor mode switch
			// Add clipboard getter
			// Add path droper

			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(windowInstance, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

			return window;
		}
		static void DestroyWindow(Window* window)
		{
			if (!windows.erase(window))
				throw std::runtime_error("Failed to remove engine window.");

			delete window;
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

	class TransformSystem final : public ecs::System<TransformSystem>
	{
	public:
		TransformSystem()
		{}

		void update(ecs::EntityManager& entities, ecs::EventManager& events, ecs::TimeDelta deltaTime) override
		{
			// TODO: paralelize this

			entities.each<TransformComponent>([deltaTime](ecs::Entity entity, TransformComponent& transformComponent)
			{
				if (entity.has_component<TranslateComponent>())
				{
					auto& translateComponent = *entity.component<TranslateComponent>();
					transformComponent.position += translateComponent.translation * static_cast<float_t>(deltaTime);
					transformComponent.isMatrixChanged = true;
				}

				if (entity.has_component<RotateComponent>())
				{
					auto& rotateComponent = *entity.component<RotateComponent>();
					transformComponent.rotation *= glm::quat(rotateComponent.rotation * static_cast<float_t>(deltaTime));
					transformComponent.isMatrixChanged = true;
				}

				if (transformComponent.isMatrixChanged)
				{
					transformComponent.matrix = glm::translate(glm::scale(glm::mat4_cast(glm::normalize(transformComponent.rotation)), transformComponent.scale), transformComponent.position);
					transformComponent.isMatrixChanged = false;
				}
			});
		}
	};

	class CameraSystem final : public ecs::System<CameraSystem>, public ecs::Receiver<CameraSystem>
	{
	private:
		Window* window;
	public:
		CameraSystem(Window* _window) :
			window(_window)
		{}

		void configure(ecs::EntityManager& entities, ecs::EventManager& events) override
		{
			events.subscribe<AspectRatioEvent>(*this);
		}

		void update(ecs::EntityManager& entities, ecs::EventManager& events, ecs::TimeDelta deltaTime) override
		{
			entities.each<CameraComponent>([](ecs::Entity entity, CameraComponent& cameraComponent)
				{
					if (cameraComponent.isMatrixChanged)
					{
						if (cameraComponent.type == CameraType::Perspective)
						{
							cameraComponent.matrix = glm::perspective(cameraComponent.fieldOfView, cameraComponent.aspectRatio,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else if (cameraComponent.type == CameraType::Orthographic)
						{
							cameraComponent.matrix = glm::ortho(cameraComponent.frustum.x, cameraComponent.frustum.y, cameraComponent.frustum.z, cameraComponent.frustum.w,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else
						{
							throw std::runtime_error("Failed to update camera: unsupported type.");
						}

						cameraComponent.isMatrixChanged = false;
					}
				});
		}

		void receive(const AspectRatioEvent& event)
		{
			auto entities = window->GetEntities();
			auto aspectRatio = event.aspectRatio;

			entities->each<CameraComponent>([aspectRatio](ecs::Entity entity, CameraComponent& cameraComponent)
				{
					if (cameraComponent.updateAspectRatio)
					{
						cameraComponent.aspectRatio = aspectRatio;
						cameraComponent.isMatrixChanged = true;
					}
				});
		}
	};

	class FirstPersonSystem final : public ecs::System<FirstPersonSystem>, public ecs::Receiver<CameraSystem>
	{
	private:
		Window* window;
		ecs::Entity camera;
		bool overviewing;
		CursorMode lastCursorMode;
		glm::vec3 overview;
	public:
		float_t sensitivity;

		FirstPersonSystem(Window* _window) :
			window(_window),
			camera(),
			overviewing(false),
			lastCursorMode(CursorMode::Normal),
			sensitivity(0.25f)
		{}

		void configure(ecs::EntityManager& entities, ecs::EventManager& events) override
		{
			events.subscribe<MouseButtonEvent>(*this);
			events.subscribe<CursorPositionEvent>(*this);

			camera = entities.create();
			camera.assign<CameraComponent>();
			camera.assign<TransformComponent>(glm::vec3(-1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
		}

		void update(ecs::EntityManager& entities, ecs::EventManager& events, ecs::TimeDelta deltaTime) override
		{
			if (overviewing && camera.has_component<TransformComponent>())
			{
				auto& transformComponent = *camera.component<TransformComponent>();
				transformComponent.rotation *= glm::quat(overview * sensitivity * static_cast<float_t>(deltaTime));
				transformComponent.isMatrixChanged = true;
			}

			overview = glm::vec3(0.0f);
		}

		void receive(const MouseButtonEvent& event)
		{
			if (event.button == MouseButtonType::Right)
			{
				if (event.action == MouseButtonAction::Press)
				{
					lastCursorMode = window->GetCursorMode();
					window->SetCursorMode(CursorMode::Disabled);
					overviewing = true;
				}
				else if (event.action == MouseButtonAction::Release)
				{
					window->SetCursorMode(lastCursorMode);
					overviewing = false;
				}
			}
		}
		void receive(const CursorPositionEvent& event)
		{
			overview += glm::vec3(static_cast<float_t>(event.deltaPosition.y), static_cast<float_t>(event.deltaPosition.x), 0.0f);
		}
	};
}
*/