#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <entt/entt.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

namespace Injector
{
	class Engine final
	{
	private:
		static bool initialized;

		static void ErrorCallback(int error, const char* description);
	public:
		static void Initialize();
		static void Terminate();

		static bool Initialized();
	};
}
