#include "Injector/Engine.hpp"
#include "Injector/Graphics/VirtualRealityEcsSystem.hpp"
#include "Injector/Graphics/AspectRatioEcsSystem.hpp"
#include "Injector/Graphics/GUI/GuiSystem.hpp"
#include "Injector/Graphics/GUI/EditorGuiHandler.hpp"
#include "Injector/Mathematics/TransformEcsSystem.hpp"

#include <iostream>

using namespace Injector;

void initialize()
{
	auto window = GpuWindow::create();

	window->setIcons(std::vector<std::shared_ptr<ImageData>>{
		ImageData::readFromFile("Resources/Images/Logo48.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo32.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo16.png", 4, false), });

	auto aspectRatioSystem = window->createSystem<AspectRatioEcsSystem>(window);
	auto guiSystem = window->createSystem<GuiSystem>();
	auto transformSystem = window->createSystem<TransformEcsSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem(window);

	auto guiCamera = window->createEntity();
	guiCamera->createComponent<TransformEcsComponent>(
		Vector3::zero,
		Quaternion(Vector3::zero),
		Vector3::one,
		RotationOrigin::Orbit);
	auto guiCameraComponent = guiCamera->createComponent<CameraEcsComponent>(
		1,
		CameraType::Orthographic,
		0.0f,
		Vector4(
			-1.0f,
			1.0f,
			-1.0f,
			1.0f),
		Vector2(
			-1.0f,
			1.0f));
	aspectRatioSystem->addCamera(guiCamera);
	guiSystem->camera = guiCamera;
	transformSystem->addTransform(guiCamera);
	cameraSystem->addCamera(guiCamera);
	renderSystem->addCamera(guiCamera);

	EditorGuiHandler::create(
		window,
		guiSystem,
		transformSystem,
		guiCameraComponent->renders);
}

int main()
{
	try
	{
		Engine::initializeGraphics(
		 	GraphicsAPI::Vulkan);
		//Engine::initializeVirtualReality();
		Engine::setTargetUpdateRate(60);
		Engine::initializeEngine();

		initialize();

		Engine::startUpdateLoop();
		Engine::terminateEngine();

		return 0;
	}
	catch (const Exception& exception)
	{
		std::cout << "Engine: " <<
			typeid(exception).name() << ": " <<
			exception.what() << "\n";

		std::cout << "PRESS ANY KEY TO EXIT";
		std::cin.get();

		return -1;
	}
}
