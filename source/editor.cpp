#include <injector/engine.hpp>
#include <injector/mathematics/transform_system.hpp>
#include <injector/mathematics/camera_system.hpp>
#include <injector/graphics/render_system.hpp>

#include <injector/glm_defines.hpp>

using namespace INJECTOR_NAMESPACE;

void init()
{
	auto window = Window::create();
	
	auto transformSystem = window->createSystem<TransformSystem>();
	auto cameraSystem = CameraSystem::create(window);
	auto renderSystem = window->createRenderSystem();

	auto camera = window->createEntity();
	camera->createComponent<TransformComponent>();
	transformSystem->addTransform(camera);

	camera->createComponent<CameraComponent>();
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);

	auto testCube = window->createEntity();
	testCube->createComponent<TransformComponent>();
	testCube->createComponent<RotateComponent>(
		Quaternion(Vector3(0.0f, 0.0f, Converter::toRadians(1.0f))));
	transformSystem->addTransform(testCube);
	auto kek = Quaternion(Vector3(0.0f, 10.0f, 0.0f)) * 0.5f;
	auto sek = glm::quat(glm::vec3(0.0f, 10.0f, 0.0f)) * 0.5f;

	kek = kek.getNormalized();
	sek = glm::normalize(sek);

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
