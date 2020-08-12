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
	auto renderSystem = RenderSystem::create(window);

	auto camera = window->createEntity();
	camera->createComponent<TransformComponent>();
	transformSystem->addTransform(camera);

	camera->createComponent<CameraComponent>();
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);

	auto testCube = window->createEntity();
	testCube->createComponent<TransformComponent>();
	transformSystem->addTransform(testCube);

	//auto colorMaterial = renderSystem->createColorMaterial(
	//  	"resources/shaders/color", "resources/shaders/color");
	auto cubeMesh = window->createCubeMesh();
	testCube->createComponent<RenderComponent>(nullptr, cubeMesh);
	renderSystem->addRender(testCube);
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
