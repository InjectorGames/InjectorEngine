#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"
#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <csignal>
#elif INJECTOR_SYSTEM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#error Unknown operating system
#endif

#if INJECTOR_SUPPORT_VIRTUAL_REALITY
#include "openvr.h"
#endif

#include "imgui.h"

#include "openssl/ssl.h"
#include "openssl/err.h"

#include <thread>
#include <iostream>

namespace Injector
{
#if INJECTOR_SUPPORT_VIRTUAL_REALITY
	static vr::TrackedDevicePose_t* renderPoses =
		new vr::TrackedDevicePose_t[vr::k_unMaxTrackedDeviceCount];

	static Matrix4 toMatrix(const vr::HmdMatrix34_t& matrix) noexcept
	{
		auto result = Matrix4(
			matrix.m[0][0], matrix.m[1][0], -matrix.m[2][0], 0.0f,
			matrix.m[0][1], matrix.m[1][1], -matrix.m[2][1], 0.0f,
				matrix.m[0][2], matrix.m[1][2], -matrix.m[2][2], 0.0f,
			matrix.m[0][3], matrix.m[1][3], -matrix.m[2][3], 1.0f).getInverted();

		result.m02 = -result.m02;
		result.m12 = -result.m12;
		result.m22 = -result.m22;
		result.m32 = -result.m32;
		return result;
	}
	static Matrix4 toMatrix(const vr::HmdMatrix44_t& matrix) noexcept
	{
		return Matrix4(
			matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], matrix.m[3][0],
			matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], matrix.m[3][1],
			-matrix.m[0][2], -matrix.m[1][2], -matrix.m[2][2], -matrix.m[3][2],
			matrix.m[0][3], matrix.m[1][3], matrix.m[2][3], matrix.m[3][3]);
	}
#endif

	bool Engine::engineInitialized = false;
	bool Engine::networkInitialized = false;
	bool Engine::graphicsInitialized = false;
	bool Engine::virtualRealityInitialized = false;

	bool Engine::updateRunning = false;
	bool Engine::capUpdateRate = true;
	int Engine::targetUpdateRate = 60;

	std::chrono::steady_clock::
		time_point Engine::updateStartTick = {};
	double Engine::updateStartTime = 0.0;
	double Engine::updateDeltaTime = 0.0;

	GraphicsAPI Engine::graphicsAPI = GraphicsAPI::Unknown;
	Matrix4 Engine::hmdModelMatrix = Matrix4::identity;
	Matrix4 Engine::leftEyeModelMatrix = Matrix4::identity;
	Matrix4 Engine::rightEyeModelMatrix = Matrix4::identity;
	Matrix4 Engine::leftEyeProjMatrix = Matrix4::identity;
	Matrix4 Engine::rightEyeProjMatrix = Matrix4::identity;

	std::vector<std::shared_ptr<EcsManager>> Engine::managers = {};

	bool Engine::getCapUpdateRate() noexcept
	{
		return capUpdateRate;
	}
	void Engine::setCapUpdateRate(bool cap) noexcept
	{
		capUpdateRate = cap;
	}

	int Engine::getTargetUpdateRate() noexcept
	{
		return targetUpdateRate;
	}
	void Engine::setTargetUpdateRate(int ups) noexcept
	{
		targetUpdateRate = ups;
	}

	std::chrono::steady_clock::
		time_point Engine::getUpdateStartTick() noexcept
	{
		return updateStartTick;
	}
	double Engine::getUpdateStartTime() noexcept
	{
		return updateStartTime;
	}
	double Engine::getUpdateDeltaTime() noexcept
	{
		return updateDeltaTime;
	}

	void Engine::initializeEngine(
		int majorVersion,
		int minorVersion,
		int patchVersion)
	{
		if (engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already initialized");
		}

		updateStartTick = std::chrono::steady_clock::now();
		updateStartTime = std::chrono::duration_cast<std::chrono::duration<
			double>>(updateStartTick.time_since_epoch()).count();
		updateDeltaTime = 0.0f;

		engineInitialized = true;

		std::cout << "Engine: Initialized (" <<
			majorVersion << "." <<
			minorVersion << "." <<
			patchVersion << ")\n";
	}
	void Engine::terminateEngine()
	{
		if (!engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already terminated");
		}
		if(updateRunning)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Update is still running");
		}

		managers.clear();

		if(networkInitialized)
			terminateNetwork();
		if (graphicsInitialized)
			terminateGraphics();
		if (virtualRealityInitialized)
			terminateVirtualReality();

		engineInitialized = false;

		std::cout << "Engine: Terminated\n";
	}
	bool Engine::isEngineInitialized() noexcept
	{
		return engineInitialized;
	}

	void Engine::initializeNetwork()
	{
		if (engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already initialized");
		}
		if (networkInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Network is already initialized");
		}

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		signal(SIGPIPE, SIG_IGN);
#elif INJECTOR_SYSTEM_WINDOWS
		WSADATA wsaData;

		auto result = WSAStartup(
			MAKEWORD(2, 2),
			&wsaData);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to startup WSA");
		}
#endif

		SSL_load_error_strings();
		OpenSSL_add_ssl_algorithms();

		networkInitialized = true;
		std::cout << "Engine: Initialized Network\n";
	}
	void Engine::terminateNetwork()
	{
		if (!engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already terminated");
		}
		if (!networkInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Network is already terminated");
		}

		EVP_cleanup();

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		signal(SIGPIPE, SIG_DFL);
#elif INJECTOR_SYSTEM_WINDOWS
		WSACleanup();
#endif

		networkInitialized = false;
		std::cout << "Engine: Terminated Network\n";
	}
	bool Engine::isNetworkInitialized()
	{
		return networkInitialized;
	}

	void Engine::glfwErrorCallback(
		int error,
		const char* description)
	{
		throw Exception(
			THIS_FUNCTION_NAME,
			std::string(description));
	}
	void Engine::initializeGraphics(
		GraphicsAPI _graphicsAPI)
	{
		if (engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already initialized");
		}
		if (graphicsInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Graphics is already initialized");
		}

		glfwSetErrorCallback(glfwErrorCallback);

		if (!glfwInit())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to initialize GLFW");
		}

		if (_graphicsAPI == GraphicsAPI::Vulkan &&
			glfwVulkanSupported() == GLFW_FALSE)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Vulkan is not supported");
		}

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		auto& style = ImGui::GetStyle();
		style.WindowTitleAlign = ImVec2(
			0.5f, 0.5f);
		style.TabRounding = 4.0f;
		style.WindowRounding = 4.0f;
		style.FrameRounding = 4.0f;
		style.GrabRounding = 4.0f;
		style.ChildRounding = 4.0f;
		style.PopupRounding = 4.0f;
		style.ScrollbarRounding = 4.0f;

		auto io = ImGui::GetIO();

		auto fonts = io.Fonts->AddFontFromFileTTF(
			"Resources/Fonts/JetBrainsMonoRegular.ttf",
			22.0f);
		fonts->Scale = 0.75;

		graphicsAPI = _graphicsAPI;
		graphicsInitialized = true;

		std::cout << "Engine: Initialized Graphics\n";
	}
	void Engine::terminateGraphics()
	{
		if (!engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already terminated");
		}
		if (!graphicsInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Graphics is already terminated");
		}

		ImGui::DestroyContext();
		glfwTerminate();

		graphicsAPI = GraphicsAPI::Unknown;
		graphicsInitialized = false;

		std::cout << "Engine: Terminated Graphics\n";
	}
	bool Engine::isGraphicsInitialized() noexcept
	{
		return graphicsInitialized;
	}

	void Engine::initializeVirtualReality()
	{
		if (engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already initialized");

		}
		if (virtualRealityInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Virtual Reality is already initialized");
		}

#if INJECTOR_SUPPORT_VIRTUAL_REALITY
		vr::EVRInitError error;

		vr::VR_Init(
			&error,
			vr::EVRApplicationType::VRApplication_Scene);

		if(error != vr::EVRInitError::VRInitError_None)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				std::string(vr::VR_GetVRInitErrorAsSymbol(error)));
		}

		virtualRealityInitialized = true;
		std::cout << "Engine: Initialized Virtual Reality\n";
#else
		throw Exception(
			THIS_FUNCTION_NAME,
			"Virtual Reality is not supported");
#endif
	}
	void Engine::terminateVirtualReality()
	{
		if (!engineInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Engine is already terminated");
		}
		if (!virtualRealityInitialized)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Virtual Reality is already terminated");
		}

#if INJECTOR_SUPPORT_VIRTUAL_REALITY
		vr::VR_Shutdown();
		virtualRealityInitialized = false;

		std::cout << "Engine: Terminated Virtual Reality\n";
#else
		throw Exception(
			THIS_FUNCTION_NAME,
			"Virtual Reality is not supported");
#endif
	}
	bool Engine::isVirtualRealityInitialized() noexcept
	{
		return virtualRealityInitialized;
	}

	void Engine::startUpdateLoop()
	{
		if (updateRunning)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already started");
		}

		updateRunning = true;

		while (updateRunning)
		{
			auto tick = std::chrono::steady_clock::now();
			updateDeltaTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick - updateStartTick).count();
			updateStartTick = tick;

			updateStartTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick.time_since_epoch()).count();

			for (auto& manager : managers)
				manager->onUpdate();

			bool existActive = false;

			for (auto& manager : managers)
			{
				if (manager->isActive())
				{
					existActive = true;
					break;
				}
			}

			if (!existActive)
				updateRunning = false;

			if (capUpdateRate)
			{
				tick = std::chrono::steady_clock::now();
				updateDeltaTime = std::chrono::duration_cast<
					std::chrono::duration<double>>(tick - updateStartTick).count();
				auto delayTime = (1.0 / targetUpdateRate - updateDeltaTime) * 1000 - 1.0;

				if (delayTime > 0)
				{
					std::this_thread::sleep_for(
						std::chrono::milliseconds(static_cast<uint64_t>(delayTime)));
				}
			}

			if (graphicsInitialized)
				glfwPollEvents();

#if INJECTOR_SUPPORT_VIRTUAL_REALITY
			if(virtualRealityInitialized)
			{
				auto vrSystem = vr::VRSystem();

				vr::VRCompositor()->WaitGetPoses(
					renderPoses,
					vr::k_unMaxTrackedDeviceCount,
					nullptr,
					0);

				auto& hmdPose = renderPoses[vr::k_unTrackedDeviceIndex_Hmd];
				hmdModelMatrix = toMatrix(hmdPose.mDeviceToAbsoluteTracking);

				leftEyeModelMatrix = toMatrix(vrSystem->GetEyeToHeadTransform(
					vr::EVREye::Eye_Left));
				rightEyeModelMatrix = toMatrix(vrSystem->GetEyeToHeadTransform(
					vr::EVREye::Eye_Right));

				leftEyeProjMatrix = toMatrix(vrSystem->GetProjectionMatrix(
					vr::EVREye::Eye_Left,
					0.1f,
					1000.0f));
				rightEyeProjMatrix = toMatrix(vrSystem->GetProjectionMatrix(
					vr::EVREye::Eye_Right,
					0.1f,
					1000.0f));

				std::cout << hmdModelMatrix.getString() << "\n";

				/*for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
				{
					auto& pose = renderPoses[i];

					if(!pose.bDeviceIsConnected || !pose.bPoseIsValid)
						continue;

					auto deviceType = vrSystem->GetTrackedDeviceClass(i);

					// TODO: add generic trackers support
					if(deviceType == vr::ETrackedDeviceClass::TrackedDeviceClass_HMD)
					{


						memcpy(&hmdVelocity, &pose.vVelocity.v, sizeof(Vector3));
					}
				}*/
			}
#endif
		}
	}
	void Engine::stopUpdateLoop() noexcept
	{
		updateRunning = false;
	}
	bool Engine::getUpdateRunning() noexcept
	{
		return updateRunning;
	}

	std::chrono::steady_clock::
		time_point Engine::getTickNow() noexcept
	{
		return std::chrono::steady_clock::now();
	}
	double Engine::getTimeNow() noexcept
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(
			std::chrono::steady_clock::now().time_since_epoch()).count();
	}

	GraphicsAPI Engine::getGraphicsAPI() noexcept
	{
		return graphicsAPI;
	}
	const Matrix4& Engine::getHmdModelMatrix() noexcept
	{
		return hmdModelMatrix;
	}
	const Matrix4& Engine::getLeftEyeModelMatrix() noexcept
	{
		return leftEyeModelMatrix;
	}
	const Matrix4& Engine::getRightEyeModelMatrix() noexcept
	{
		return rightEyeModelMatrix;
	}
	const Matrix4& Engine::getLeftEyeProjMatrix() noexcept
	{
		return leftEyeProjMatrix;
	}
	const Matrix4& Engine::getRightEyeProjMatrix() noexcept
	{
		return rightEyeProjMatrix;
	}

	bool Engine::addManager(
		const std::shared_ptr<EcsManager>& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		managers.push_back(manager);
		return true;
	}
	bool Engine::removeManager(
		const std::shared_ptr<EcsManager>& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		for (auto i = managers.begin(); i != managers.end(); i++)
		{
			if (manager == *i)
			{
				managers.erase(i);
				return true;
			}
		}

		return false;
	}
	bool Engine::containsManager(
		const std::shared_ptr<EcsManager>& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		for (auto& i : managers)
		{
			if (manager == i)
				return true;
		}

		return false;
	}
	void Engine::removeManagers() noexcept
	{
		managers.clear();
	}
	size_t Engine::getManagerCount() noexcept
	{
		return managers.size();
	}
}
