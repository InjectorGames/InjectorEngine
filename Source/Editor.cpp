#include "Injector/Engine.hpp"
#include "Injector/Graphics/GuiEcsSystem.hpp"
#include "Injector/Graphics/AspectRatioEcsSystem.hpp"
#include "Injector/Mathematics/TransformEcsSystem.hpp"
#include "Injector/Graphics/GUI/EditorGuiHandler.hpp"

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
	auto guiSystem = window->createSystem<GuiEcsSystem>(window);
	auto transformSystem = window->createSystem<TransformEcsSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem(window);

	guiSystem->initialize(
		transformSystem,
		cameraSystem,
		renderSystem);

	auto editor = EcsEntity::create();
	editor->createComponent<GuiEcsComponent>(
		std::make_shared<EditorGuiHandler>());
	guiSystem->addGui(editor);
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
