#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/VkWindow.hpp"

#include <thread>
#include <iostream>

#if INJECTOR_SUPPORT_VR
#include "openvr.h"
#endif

namespace Injector
{
#if INJECTOR_SUPPORT_VR
	static vr::TrackedDevicePose_t* renderPoses =
		new vr::TrackedDevicePose_t[vr::k_unMaxTrackedDeviceCount];

	static Matrix4 toMatrix(const vr::HmdMatrix34_t& matrix) noexcept
	{
		auto result = Matrix4(
			matrix.m[0][0], matrix.m[1][0], -matrix.m[2][0], 0.0f,
			matrix.m[0][1], matrix.m[1][1], -matrix.m[2][1], 0.0f,
				matrix.m[0][2], matrix.m[1][2], -matrix.m[2][2], 0.0f,
			matrix.m[0][3], matrix.m[1][3], -matrix.m[2][3], 1.0f).getInversed();

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
	bool Engine::videoInitialized = false;
	bool Engine::vrInitialized = false;

	bool Engine::updateRunning = false;
	bool Engine::capUpdateRate = true;
	int Engine::targetUpdateRate = 60;

	std::chrono::steady_clock::
		time_point Engine::updateStartTick = {};
	double Engine::updateStartTime = 0.0;
	double Engine::updateDeltaTime = 0.0;

	GraphicsAPI Engine::graphicsApi = GraphicsAPI::Unknown;
	Matrix4 Engine::hmdModelMatrix = Matrix4::identity;
	Matrix4 Engine::leftEyeModelMatrix = Matrix4::identity;
	Matrix4 Engine::rightEyeModelMatrix = Matrix4::identity;
	Matrix4 Engine::leftEyeProjMatrix = Matrix4::identity;
	Matrix4 Engine::rightEyeProjMatrix = Matrix4::identity;

	std::vector<std::shared_ptr<Manager>> Engine::managers = {};

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
				"Engine",
				"initializeEngine",
				"Already initialized");
		}

		updateStartTick =
			std::chrono::high_resolution_clock::now();
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
				"Engine",
				"terminateEngine",
				"Already terminated");
		}
		if(updateRunning)
		{
			throw Exception(
				"Engine",
				"terminateEngine",
				"Update is still running");
		}

		managers.clear();

		if (videoInitialized)
			terminateVideo();
		if (vrInitialized)
			terminateVr();

		engineInitialized = false;

		std::cout << "Engine: Terminated\n";
	}
	bool Engine::getEngineInitialized() noexcept
	{
		return engineInitialized;
	}

	void Engine::videoErrorCallback(
		int error, const char* description)
	{
		throw Exception(
			"Engine",
			"videoErrorCallback",
			std::string(description));
	}
	void Engine::initializeVideo(
		GraphicsAPI _graphicsApi)
	{
		if (engineInitialized)
		{
			throw Exception(
				"Engine",
				"initializeVideo",
				"Engine is already initialized");

		}
		if (videoInitialized)
		{
			throw Exception(
				"Engine",
				"initializeVideo",
				"Video is already initialized");
		}

		glfwSetErrorCallback(videoErrorCallback);

		if (!glfwInit())
		{
			throw Exception(
				"Engine",
				"initializeVideo",
				"Failed to initialize GLFW");
		}

		if (_graphicsApi == GraphicsAPI::Vulkan && glfwVulkanSupported() == GLFW_FALSE)
		{
			throw Exception(
				"Engine",
				"initializeVideo",
				"Vulkan is not supported");
		}

		graphicsApi = _graphicsApi;
		videoInitialized = true;

		std::cout << "Engine: Initialized Video\n";
	}
	void Engine::terminateVideo()
	{
		if (!engineInitialized)
		{
			throw Exception(
				"Engine",
				"terminateVideo",
				"Engine is already terminated");
		}
		if (!videoInitialized)
		{
			throw Exception(
				"Engine",
				"terminateVideo",
				"Video is already terminated");
		}

		glfwTerminate();

		graphicsApi = GraphicsAPI::Unknown;
		videoInitialized = false;

		std::cout << "Engine: Terminated Video\n";
	}
	bool Engine::getVideoInitialized() noexcept
	{
		return videoInitialized;
	}

	void Engine::initializeVr()
	{
		if (engineInitialized)
		{
			throw Exception(
				"Engine",
				"initializeVr",
				"Engine is already initialized");

		}
		if (vrInitialized)
		{
			throw Exception(
				"Engine",
				"initializeVr",
				"VR is already initialized");
		}

#if INJECTOR_SUPPORT_VR
		vr::EVRInitError error;

		vr::VR_Init(&error,
			vr::EVRApplicationType::VRApplication_Scene);

		if(error != vr::EVRInitError::VRInitError_None)
		{
			throw Exception(
				"Engine",
				"initializeVr",
				std::string(vr::VR_GetVRInitErrorAsSymbol(error)));
		}

		vrInitialized = true;
		std::cout << "Engine: Initialized VR\n";
#else
		throw Exception(
			"Engine",
			"initializeVr",
			"VR is not supported");
#endif
	}
	void Engine::terminateVr()
	{
		if (!engineInitialized)
		{
			throw Exception(
				"Engine",
				"terminateVr",
				"Engine is already terminated");
		}
		if (!vrInitialized)
		{
			throw Exception(
				"Engine",
				"terminateVr",
				"VR is already terminated");
		}

#if INJECTOR_SUPPORT_VR
		vr::VR_Shutdown();
		vrInitialized = false;

		std::cout << "Engine: Terminated VR\n";
#else
		throw Exception(
			"Engine",
			"initializeVr",
			"VR is not supported");
#endif
	}
	bool Engine::getVrInitialized() noexcept
	{
		return vrInitialized;
	}

	void Engine::startUpdateLoop()
	{
		if (updateRunning)
		{
			throw Exception(
				"Engine",
				"startUpdateLoop",
				"Already started");
		}

		updateRunning = true;

		while (updateRunning)
		{
			auto tick = std::chrono::high_resolution_clock::now();
			updateDeltaTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick - updateStartTick).count();
			updateStartTick = tick;

			updateStartTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick.time_since_epoch()).count();

			for (auto& manager : managers)
				manager->update();

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
				tick = std::chrono::high_resolution_clock::now();
				updateDeltaTime = std::chrono::duration_cast<
					std::chrono::duration<double>>(tick - updateStartTick).count();
				auto delayTime = (1.0 / targetUpdateRate - updateDeltaTime) * 1000 - 1.0;

				if (delayTime > 0)
				{
					std::this_thread::sleep_for(
						std::chrono::milliseconds(static_cast<uint64_t>(delayTime)));
				}
			}

			if (videoInitialized)
				glfwPollEvents();

#if INJECTOR_SUPPORT_VR
			if(vrInitialized)
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
	void Engine::stopUpdateLoop()
	{
		if (!updateRunning)
		{
			throw Exception(
				"Engine",
				"stopUpdateLoop",
				"Already stopped");
		}

		updateRunning = false;
	}
	bool Engine::getUpdateRunning() noexcept
	{
		return updateRunning;
	}

	std::chrono::steady_clock::
		time_point Engine::getTickNow() noexcept
	{
		return std::chrono::high_resolution_clock::now();
	}
	double Engine::getTimeNow() noexcept
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}

	GraphicsAPI Engine::getGraphicsApi() noexcept
	{
		return graphicsApi;
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
		const std::shared_ptr<Manager>& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		managers.push_back(manager);
		return true;
	}
	bool Engine::removeManager(
		const std::shared_ptr<Manager>& manager) noexcept
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
		const std::shared_ptr<Manager>& manager) noexcept
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
