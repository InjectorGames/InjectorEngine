#include "Injector/Engine.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Mathematics/TransformSystem.hpp"
#include "Injector/Graphics/FlyTransformSystem.hpp"

using namespace Injector;

void init()
{
	auto window = Window::create();

	auto flyTransformSystem = window->createSystem<FlyTransformSystem>(window);
	auto transformSystem = window->createSystem<TransformSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem();

	auto camera = window->createEntity();
	camera->createComponent<TransformComponent>(Vector3(0.0f, -2.5f, 5.0f), 
		Quaternion::zero, Vector3::one, RotationOrigin::Orbit);
	auto cameraComponent = camera->createComponent<CameraComponent>();
	flyTransformSystem->transform = camera;
	transformSystem->addTransform(camera);
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);
	
	auto colorPipeline = window->createDiffusePipeline();
	//auto boxTexture = window->createTexture();
	auto squareMesh = window->createSquareMeshVN(true);
	auto cubeMesh = window->createCubeMeshVN(true);

	auto floor = window->createEntity();
	floor->createComponent<TransformComponent>(Vector3::zero,
		Quaternion(Vector3(Converter::toRadians(-90.0f), 0.0f, 0.0f)), Vector3::one * 10);
	floor->createComponent<RenderComponent>(colorPipeline, squareMesh);
	transformSystem->addTransform(floor);
	cameraComponent->renders.emplace(floor);

	auto cube1 = window->createEntity();
	cube1->createComponent<TransformComponent>(Vector3(-5.0f, 0.5f, -5.0f));
	cube1->createComponent<RenderComponent>(colorPipeline, cubeMesh);
	transformSystem->addTransform(cube1);
	cameraComponent->renders.emplace(cube1);
	
	window->show();
}

int main(int argc, char* args[])
{
	//Engine::initializeEvents();
	//Engine::initializeVideo(GraphicsApi::Vulkan);
	Engine::initializeVideo(GraphicsApi::OpenGL);
	Engine::initializeEngine();

	init();

	Engine::startUpdateLoop();
	Engine::terminateEngine();

	return 0;
}
