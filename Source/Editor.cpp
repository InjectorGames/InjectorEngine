#include "Injector/Engine.hpp"
#include "Injector/Graphics/VrSystem.hpp"
#include "Injector/Graphics/GuiSystem.hpp"
#include "Injector/Graphics/SimSkySystem.hpp"
#include "Injector/Graphics/FreeCameraSystem.hpp"
#include "Injector/Mathematics/TransformSystem.hpp"

#include <iostream>

using namespace Injector;

void initialize()
{
	auto window = Window::create();

	window->setIcons(std::vector<std::shared_ptr<ImageData>>{
		ImageData::readFromFile("Resources/Images/Logo48.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo32.png", 4, false),
		ImageData::readFromFile("Resources/Images/Logo16.png", 4, false), });

	auto freeCameraSystem = window->createSystem<FreeCameraSystem>(window);
	auto guiSystem = window->createSystem<GuiSystem>();
	auto simSkySystem = window->createSystem<SimSkySystem>(window);
	//auto vrSystem = window->createSystem<VrSystem>();
	auto transformSystem = window->createSystem<TransformSystem>();
	auto cameraSystem = window->createCameraSystem(window);
	auto renderSystem = window->createRenderSystem(window);

	auto freeCamera = window->createEntity();
	freeCamera->createComponent<TransformComponent>(
		Vector3(0.0f, 0, 0),
		Quaternion(Vector3::zero),
		Vector3::one,
		RotationOrigin::Orbit);
	auto freeCameraComponent = freeCamera->createComponent<CameraComponent>(
		0,
		CameraType::Perspective);
	transformSystem->addTransform(freeCamera);
	//vrSystem->hmd = freeCamera;
	cameraSystem->addCamera(freeCamera);
	renderSystem->addCamera(freeCamera);
	freeCameraSystem->camera = freeCamera;

	auto guiCamera = window->createEntity();
	guiCamera->createComponent<TransformComponent>(
		Vector3::zero,
		Quaternion(Vector3::zero),
		Vector3::one,
		RotationOrigin::Orbit);
	auto guiCameraComponent = guiCamera->createComponent<CameraComponent>(
		1,
		CameraType::Orthographic);
	transformSystem->addTransform(guiCamera);
	cameraSystem->addCamera(guiCamera);
	renderSystem->addCamera(guiCamera);

	auto imageDiffuseVertexShader = window->createShader(
		GpuShaderStage::Vertex,
		window->readShaderData(
			"Resources/Shaders/ImageDiffuse.vert"));
	auto imageDiffuseFragmentShader = window->createShader(
		GpuShaderStage::Fragment,
		window->readShaderData(
			"Resources/Shaders/ImageDiffuse.frag"));
	auto boxImageData = ImageData::readFromFile(
		"Resources/Images/GrayBox.png",
		4,
		false);
	auto boxImage = window->createImage(
		GpuImageFormat::RGBA8,
 		boxImageData->size,
		true,
		boxImageData);
	auto imageDiffusePipeline = window->createImageDiffusePipeline(
		GpuDrawMode::TriangleList,
		GpuImageFilter::Nearest,
		GpuImageFilter::Nearest,
		GpuImageFilter::Linear,
		GpuImageWrap::Repeat,
		GpuImageWrap::Repeat,
		GpuImageWrap::Repeat,
		imageDiffuseVertexShader,
		imageDiffuseFragmentShader,
		boxImage);

	/*auto simSkyVertexShader = window->createShader(
		GpuShaderStage::Vertex,
		window->readShaderData(
			"Resources/Shaders/SimulatedSky.vert"));
	auto simSkyFragmentShader = window->createShader(
		GpuShaderStage::Fragment,
		window->readShaderData(
			"Resources/Shaders/SimulatedSky.frag"));
	auto simSkyPipeline = window->createSkyPipeline(
		PrimitiveTopology::TriangleList,
		simSkyVertexShader,
		simSkyFragmentShader);*/

	auto teapotModelData = ModelData::readFromFile(
		"Resources/Models/UtahTeapot.fbx");

	auto simSkyMesh = window->createMesh(
		ModelData::frame.getVertex(),
		false,
		ModelData::frame.indices,
		false);
	auto floorMesh = window->createMesh(
		ModelData::square.getVertexNormalTexCoord(),
		false,
		ModelData::square.indices,
		false);
	auto cubeMesh = window->createMesh(
		ModelData::cube.getVertexNormalTexCoord(),
		false,
		ModelData::cube.indices,
		false);
	auto teapotMesh = window->createMesh(
		teapotModelData->getVertexNormalTexCoord(),
		false,
		teapotModelData->indices,
		false);

	/*auto simSky = window->createEntity();
	simSky->createComponent<TransformComponent>(
		Vector3(0.0f, 0.0f, 10.0f));
	simSky->createComponent<RenderComponent>(
		simSkyPipeline,
		simSkyMesh);
	transformSystem->addTransform(simSky);
	freeCameraComponent->renders.emplace(simSky);*/

	auto floor = window->createEntity();
	floor->createComponent<TransformComponent>(
		Vector3::zero,
		Quaternion(
			Vector3(
				Converter::toRadians(-90.0f),
				0.0f,
				0.0f)),
		Vector3::one * 10);
	floor->createComponent<RenderComponent>(
		imageDiffusePipeline,
		floorMesh);
	transformSystem->addTransform(floor);
	freeCameraComponent->renders.emplace(floor);

	auto cube = window->createEntity();
	cube->createComponent<TransformComponent>(
		Vector3(-4.5f, 0.5f, -4.5f),
		Quaternion(Vector3::zero),
		Vector3::one,
		RotationOrigin::Spin,
		Matrix4::identity,
		nullptr);
	cube->createComponent<RenderComponent>(
		imageDiffusePipeline,
		cubeMesh);
	transformSystem->addTransform(cube);
	freeCameraComponent->renders.emplace(cube);

	auto teapot = window->createEntity();
	teapot->createComponent<TransformComponent>(
		Vector3(0.0f, 0.5f, 0.0f),
		Quaternion(Vector3::zero),
		Vector3::one / 8.0f,
		RotationOrigin::Spin,
		Matrix4::identity,
		cube);
	teapot->createComponent<RenderComponent>(
		imageDiffusePipeline,
		teapotMesh);
	transformSystem->addTransform(teapot);
	freeCameraComponent->renders.emplace(teapot);
}

int main()
{
	try
	{
		Engine::initializeGraphics(
		 	GraphicsAPI::Vulkan);
		//Engine::initializeVirtualReality();
		Engine::setTargetUpdateRate(60);
		Engine::initializeEngine();

		initialize();

		Engine::startUpdateLoop();
		Engine::terminateEngine();

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << "Engine: " <<
			typeid(exception).name() << ": " <<
			exception.what() << "\n";

		std::cout << "PRESS ANY KEY TO EXIT";
		std::cin.get();

		return -1;
	}
}
