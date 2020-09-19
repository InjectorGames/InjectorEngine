#include "Injector/Engine.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Mathematics/TransformSystem.hpp"
#include "Injector/Graphics/FlyTransformSystem.hpp"

using namespace Injector;

void init()
{
	auto window = Window::create();

	window->setIcons(std::vector<std::shared_ptr<ImageData>>{
		ImageData::readFromFile("Resources/Images/Logo16.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo32.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo48.png", 4, false),
	});

	auto flyTransformSystem = window->createSystem<FlyTransformSystem>(window);
	auto transformSystem = window->createSystem<TransformSystem>();
	auto cameraSystem = window->createCameraSystem();
	auto renderSystem = window->createRenderSystem();

	auto fpvCamera = window->createEntity();
	fpvCamera->createComponent<TransformComponent>(Vector3(0.0f, -2.5f, 5.0f),
		Quaternion(Vector3::zero), Vector3::one, RotationOrigin::Orbit);
	auto fpvCameraComponent = fpvCamera->createComponent<CameraComponent>();
	transformSystem->addTransform(fpvCamera);
	cameraSystem->addCamera(fpvCamera);
	renderSystem->addCamera(fpvCamera);
	flyTransformSystem->transform = fpvCamera;

	auto texDiffuseVertexShader = window->createShader(GpuShaderStage::Vertex,
		window->readShaderData("Resources/Shaders/TexDiffuse.vert"));
	auto texDiffuseFragmentShader = window->createShader(GpuShaderStage::Fragment,
		window->readShaderData("Resources/Shaders/TexDiffuse.frag"));
	auto boxImageData = ImageData::readFromFile(
		"Resources/Images/GrayBox.png", 3, false);
	auto boxImage = window->createImage(boxImageData->size,
		GpuImageFormat::RGB8, GpuImageFilter::Nearest, GpuImageFilter::Nearest,
		GpuImageWrap::Repeat, GpuImageWrap::Repeat, true, boxImageData);
	auto texDiffusePipeline = window->createTexDiffusePipeline(
		texDiffuseVertexShader, texDiffuseFragmentShader, boxImage);

	auto skyVertexShader = window->createShader(GpuShaderStage::Vertex,
		window->readShaderData("Resources/Shaders/Sky.vert"));
	auto skyFragmentShader = window->createShader(GpuShaderStage::Fragment,
		window->readShaderData("Resources/Shaders/Sky.frag"));
	auto skyPipeline = window->createSkyPipeline(
		skyVertexShader, skyFragmentShader);

	auto sky = window->createEntity();
	auto skyMesh = window->createCubeMeshVNT(false);
	sky->createComponent<TransformComponent>(Vector3(0.0f, 0.0f, 10.0f));
	sky->createComponent<RenderComponent>(texDiffusePipeline, skyMesh);
	transformSystem->addTransform(sky);
	fpvCameraComponent->renders.emplace(sky);

	//auto teapotModelData = 

	auto floor = window->createEntity();
	auto squareMesh = window->createSquareMeshVNT(false);
	floor->createComponent<TransformComponent>(Vector3::zero,
		Quaternion(Vector3(Converter::toRadians(-90.0f), 0.0f, 0.0f)), Vector3::one * 10);
	floor->createComponent<RenderComponent>(texDiffusePipeline, squareMesh);
	transformSystem->addTransform(floor);
	fpvCameraComponent->renders.emplace(floor);

	auto cube = window->createEntity();
	auto cubeMesh = window->createCubeMeshVNT(false);
	cube->createComponent<TransformComponent>(Vector3(-4.5f, 0.5f, -4.5f));
	cube->createComponent<RenderComponent>(texDiffusePipeline, cubeMesh);
	transformSystem->addTransform(cube);
	fpvCameraComponent->renders.emplace(cube);
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
