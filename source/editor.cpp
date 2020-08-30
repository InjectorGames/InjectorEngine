#include <injector/engine.hpp>
#include <injector/graphics/camera_system.hpp>
#include <injector/graphics/render_system.hpp>
#include <injector/mathematics/transform_system.hpp>
#include <injector/graphics/fly_transform_system.hpp>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <injector/glm_defines.hpp>

using namespace INJECTOR_NAMESPACE;

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
	Engine::initializeEvents();
	Engine::initializeVideo(GraphicsAPI::Vulkan);
	//Engine::initializeVideo(GraphicsAPI::OpenGL);
	Engine::initializeEngine();

	init();

	Engine::startUpdateLoop();
	Engine::terminateEngine();

	return 0;
}
