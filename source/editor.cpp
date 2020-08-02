#include <injector/engine.hpp>
#include <injector/window_system.hpp>
#include <injector/render_system.hpp>
#include <injector/camera_system.hpp>
#include <injector/transform_system.hpp>

#include <injector/glm_defines.hpp>

using namespace INJECTOR_NAMESPACE;

int main(int argc, char* args[])
{
	Engine::initializeVideo(GraphicsAPI::Vulkan);
	Engine::initializeEngine();

	//auto mat = glm::mat4(0);
	//glm::perspective

	auto manager = Engine::createManager<Manager>();
	auto windowSystem = manager->createSystem<WindowSystem>();
	auto transformSystem = manager->createSystem<TransformSystem>();
	auto cameraSystem = manager->createSystem<CameraSystem>();
	auto renderSystem = manager->createSystem<RenderSystem>();

	auto window = manager->createEntity();

	windowSystem->createWindowComponent(window);
	windowSystem->addWindow(window);
	cameraSystem->window = window;
	renderSystem->window = window;

	auto camera = manager->createEntity();
	camera->createComponent<TransformComponent>();
	camera->createComponent<CameraComponent>();
	transformSystem->addTransform(camera);
	cameraSystem->addCamera(camera);
	renderSystem->addCamera(camera);

	auto testCube = manager->createEntity();
	testCube->createComponent<TransformComponent>();
	//auto colorMaterial = renderSystem->createColorMaterial(
	//  	"resources/shaders/color", "resources/shaders/color");

	testCube->createComponent<RenderComponent>();
	transformSystem->addTransform(testCube);
	renderSystem->addRender(testCube);

	Engine::startUpdateLoop();
	Engine::terminateEngine();
	return 0;
}
