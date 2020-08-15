#include <injector/engine.hpp>
#include <injector/graphics/window.hpp>
#include <injector/graphics/camera_system.hpp>
#include <injector/graphics/render_system.hpp>
#include <injector/graphics/fly_camera_system.hpp>
#include <injector/mathematics/transform_system.hpp>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <injector/glm_defines.hpp>

using namespace INJECTOR_NAMESPACE;

void init()
{
	auto window = Window::create();
	
	auto flyCameraSystem = window->createSystem<FlyCameraSystem>();
	auto transformSystem = window->createSystem<TransformSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem();
	
	auto camera = window->createEntity();
	camera->createComponent<TransformComponent>();
	transformSystem->addTransform(camera);

	camera->createComponent<CameraComponent>();
	flyCameraSystem->camera = camera;
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);

	auto testCube = window->createEntity();
	testCube->createComponent<TransformComponent>(
		nullptr, Vector3(0.0f, 0.0f, 2.0f));
	testCube->createComponent<RotateComponent>(
		Quaternion(Vector3(0.0f, 0.0f, Converter::toRadians(1.0f))));
	transformSystem->addTransform(testCube);

	auto colorPipeline = window->createColorPipeline();
	auto squareMesh = window->createSquareMesh();
	testCube->createComponent<RenderComponent>(colorPipeline, squareMesh);
	renderSystem->addRender(testCube);

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
