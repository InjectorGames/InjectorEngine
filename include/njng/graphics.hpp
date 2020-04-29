#pragma once
#include <njng/defines.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

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

#include <dear-imgui/imgui.h>

#include <iostream>

namespace njng
{
	typedef GLFWwindow* window_t;

	class Graphics final
	{
	public:
		using UpdatePFN = void(*)(const double&);
		using RenderPFN = void(*)();
	private:
		inline static bool m_initialized = false;
		inline static window_t m_window = nullptr;

		inline static void errorCallback(int error, const char* description)
		{
			std::cerr << "GLFW error: Code = " << error << ", Description = " << description << ".\n";
		}

		inline static void initializeGLFW()
		{
			glfwSetErrorCallback(errorCallback);

			if (!glfwInit())
				throw std::runtime_error("Failed to intialize GLFW.");
		}
		inline static void terminateGLFW()
		{
			glfwTerminate();
		}

		inline static window_t createWindow()
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			return static_cast<window_t>(glfwCreateWindow(DefaultWindowWidth, DefaultWindowHeight, DefaultWindowName, nullptr, nullptr));
		}
		inline static void destroyWindow(window_t window)
		{
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if USE_WAYLAND
			auto win_impl = static_cast<wl_egl_window*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (win_impl)
			{
				glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window), nullptr);
				wl_egl_window_destroy(win_impl);
			}
#	endif
#endif
			glfwDestroyWindow(static_cast<GLFWwindow*>(window));
		}

		inline static void initializeBGFX(window_t window)
		{
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
			auto  win_impl = static_cast<wl_egl_window*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!win_impl)
			{
				int width, height;
				glfwGetWindowSize(_window, &width, &height);

				auto surface = static_cast<struct wl_surface*>(glfwGetWaylandWindow(static_cast<GLFWwindow*>(window)));

				if (surface)
				{
					win_impl = wl_egl_window_create(surface, width, height);
					glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window), static_cast<void*>(static_cast<uintptr_t>(win_impl)));
				}
			}
			pd.nwh = static_cast<void*>(static_cast<uintptr_t>(win_impl));
#	else
			pd.nwh = static_cast<void*>(static_cast<uintptr_t>(glfwGetX11Window(static_cast<GLFWwindow*>(window))));
#	endif
#elif BX_PLATFORM_OSX
			pd.nwh = glfwGetCocoaWindow(static_cast<GLFWwindow*>(window));
#elif BX_PLATFORM_WINDOWS
			pd.nwh = glfwGetWin32Window(static_cast<GLFWwindow*>(window));
#endif
			bgfx::setPlatformData(pd);

			bgfx::Init bgfxInit = {};
			bgfxInit.type = bgfx::RendererType::Count;
			bgfxInit.resolution.width = DefaultWindowWidth;
			bgfxInit.resolution.height = DefaultWindowHeight;
			bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

			if (!bgfx::init(bgfxInit))
				throw std::runtime_error("Failed to intialize BGFX.");

			bgfx::setDebug(BGFX_DEBUG_TEXT);
			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		}
		inline static void terminateBGFX()
		{
			bgfx::shutdown();
		}
	public:
		inline static void initialize()
		{
			if (m_initialized)
				throw std::runtime_error("Graphics already initialized");

			initializeGLFW();

			m_window = createWindow();

			initializeBGFX(m_window);
			m_initialized = true;
		}
		inline static void terminate()
		{
			if (!m_initialized)
				throw std::runtime_error("Graphics is not initialized");

			terminateBGFX();

			if (m_window)
			{
				destroyWindow(m_window);
				m_window = nullptr;
			}

			terminateGLFW();
			m_initialized = false;
		}
		inline static void update(const UpdatePFN& update)
		{
			if (!update)
				throw std::runtime_error("Update function pointer is null");

			double lastTime = 0;

			while (!glfwWindowShouldClose(m_window))
			{
				auto time = glfwGetTime();
				update(time - lastTime);
				lastTime = time;
				glfwPollEvents();
			}
		}
		inline static void render(const RenderPFN& render)
		{
			bgfx::setViewRect(0, 0, 0, 800, 600);
			bgfx::touch(0);
			render();
			bgfx::frame();
		}

		inline static bool initialized()
		{
			return m_initialized;
		}
		inline static window_t window()
		{
			return m_window;
		}
	};
}
