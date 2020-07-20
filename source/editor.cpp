#include <injector/engine.hpp>
#include <injector/window_system.hpp>
#include <injector/render_system.hpp>
//#include <injector/gl/editor_window.hpp>

#include <injector/glm_defines.hpp>

#include <injector/matrix4.hpp>
#include <injector/matrix2.hpp>
#include <injector/matrix3.hpp>

using namespace INJECTOR_NAMESPACE;

int main(int argc, char* args[])
{
	Engine::initializeVideo();
	Engine::initializeEngine();

	auto manager = Engine::createManager<Manager>();
	auto windowSystem = manager->createSystem<WindowSystem>();
	auto renderSystem = manager->createSystem<RenderSystem>();

	auto window = manager->createEntity();
	windowSystem->createWindowComponent(window);
	renderSystem->window = window;

	auto mat1 = Matrix4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	auto mat2 = Matrix4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

	auto matt1 = glm::mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	auto matt2 = glm::mat4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

	//glm::inverse
	auto keks = glm::quat() * glm::quat();
	auto kek1 = mat1.getDot(mat2);
	auto kek2 = matt2 * matt1;

	auto mat11 = Matrix3(1, 2, 1, 2, 1, 2, 1, 2, 1);
	auto mat22 = glm::mat3(1, 2, 1, 2, 1, 2, 1, 2, 1);

	mat11 = mat11.getInversed();
	mat22 = glm::inverse(mat22);

	Engine::startUpdateLoop();
	Engine::terminateEngine();
	return 0;
}
