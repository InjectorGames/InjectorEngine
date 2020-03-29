#pragma once
#include <engine.hpp>

namespace Injector
{
	class Window
	{
	protected:
		GLFWwindow* instance;

		virtual void SetWindowHints();
	public:
		Window(int width = 800, int height = 600, const std::string& title = "Injector Engine - Editor", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		virtual void BeginUpdate();
	};
}
