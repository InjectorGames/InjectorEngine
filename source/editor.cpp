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
	camera->createComponent<TransformComponent>(Vector3(0.0f, 2.0f, 4.0f), 
		Quaternion(Vector3::zero), Vector3::one, RotationOrigin::Orbit);
	transformSystem->addTransform(camera);

	camera->createComponent<CameraComponent>();
	flyTransformSystem->transform = camera;
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);

	auto floor = window->createEntity();
	floor->createComponent<TransformComponent>(Vector3::zero,
		Quaternion(Vector3(Converter::toRadians(90.0f), 0.0f, 0.0f)), Vector3::one * 8);

	auto colorPipeline = window->createColorPipeline();
	auto squareMesh = window->createSquareMesh();
	floor->createComponent<RenderComponent>(colorPipeline, squareMesh);

	transformSystem->addTransform(floor);
	renderSystem->addRender(floor);

	window->show();
}

int main(int argc, char* args[])
{
	Engine::initializeEvents();
	Engine::initializeVideo(GraphicsAPI::Vulkan);
	Engine::initializeEngine();

	init();

	Engine::startUpdateLoop();
	Engine::terminateEngine();

	return 0;
}
