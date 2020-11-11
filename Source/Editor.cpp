#include "Injector/Engine.hpp"
#include "Injector/Graphics/VirtualRealityEcsSystem.hpp"
#include "Injector/Graphics/AspectRatioEcsSystem.hpp"
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
	auto transformSystem = window->createSystem<TransformEcsSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem(window);
}

int main()
{
	try
	{
		Engine::initializeGraphics(
		 	GraphicsAPI::OpenGL);
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
