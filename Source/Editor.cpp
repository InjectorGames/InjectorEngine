#include "Injector/Engine.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Mathematics/TransformSystem.hpp"
#include "Injector/Graphics/FlyTransformSystem.hpp"

using namespace Injector;

void init()
{
	auto window = Window::create();

	window->setIcons(std::vector<std::shared_ptr<ImageData>>
	{
		ImageData::readFromFile("Resources/Images/Logo16.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo32.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo48.png", 4, false),
	});

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
	
	auto vertexShader = window->createShader(GpuShaderStage::Vertex,
		window->readShaderData("Resources/Shaders/TexDiffuse.vert"));
	auto fragmentShader = window->createShader(GpuShaderStage::Fragment,
		window->readShaderData("Resources/Shaders/TexDiffuse.frag"));
	auto boxImageData = ImageData::readFromFile(
		"Resources/Images/GrayBox.png", 3, false);
	auto boxImage = window->createImage(boxImageData->size,
		GpuImageFormat::RGB8, GpuImageFilter::Nearest, GpuImageFilter::Nearest,
		GpuImageWrap::Repeat, GpuImageWrap::Repeat, true, boxImageData);
	auto pipeline = window->createTexDiffusePipeline(
		vertexShader, fragmentShader, boxImage);
	auto squareMesh = window->createSquareMeshVNT(false);
	auto cubeMesh = window->createCubeMeshVNT(false);

	auto floor = window->createEntity();
	floor->createComponent<TransformComponent>(Vector3::zero,
		Quaternion(Vector3(Converter::toRadians(-90.0f), 0.0f, 0.0f)), Vector3::one * 10);
	floor->createComponent<RenderComponent>(pipeline, squareMesh);
	transformSystem->addTransform(floor);
	cameraComponent->renders.emplace(floor);

	auto cube1 = window->createEntity();
	cube1->createComponent<TransformComponent>(Vector3(-4.5f, 0.5f, -4.5f));
	cube1->createComponent<RenderComponent>(pipeline, cubeMesh);
	transformSystem->addTransform(cube1);
	cameraComponent->renders.emplace(cube1);
}

int main(int argc, char* args[])
{
	//Engine::initializeVideo(GraphicsApi::Vulkan);
	Engine::initializeVideo(GraphicsApi::OpenGL);
	Engine::initializeEngine();

	init();

	Engine::startUpdateLoop();
	Engine::terminateEngine();

	return 0;
}
