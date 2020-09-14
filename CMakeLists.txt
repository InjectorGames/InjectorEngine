cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(InjectorEngine
	VERSION 1.0.0
	LANGUAGES CXX
)

option(INJECTOR_BUILD_EDITOR "Build editor executable" ON)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(TestBigEndian)
TEST_BIG_ENDIAN(INJECTOR_BIG_ENDIAN)

set(INJECTOR_POINTER_SIZE ${CMAKE_SIZEOF_VOID_P})
set(INJECTOR_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set(INJECTOR_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(INJECTOR_SYSTEM_32 1)
	set(INJECTOR_SYSTEM_64 0)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(INJECTOR_SYSTEM_32 0)
	set(INJECTOR_SYSTEM_64 1)
else()
	message(FATAL_ERROR "Failed to detect system architecture")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(INJECTOR_SYSTEM_LINUX 1)
	set(INJECTOR_SYSTEM_WINDOWS 0)
	set(INJECTOR_SYSTEM_MACOS 0)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(INJECTOR_SYSTEM_LINUX 0)
	set(INJECTOR_SYSTEM_WINDOWS 1)
	set(INJECTOR_SYSTEM_MACOS 0)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(INJECTOR_SYSTEM_LINUX 0)
	set(INJECTOR_SYSTEM_WINDOWS 0)
	set(INJECTOR_SYSTEM_MACOS 1)
else()
	message(FATAL_ERROR "Failed to detect system name")
endif()

include(FindVulkan)
include(CMake/asio.cmake)
include(CMake/stb.cmake)
include(CMake/VulkanMemoryAllocator.cmake)

set(BUILD_UTILS OFF CACHE BOOL "")
set(GLEW_REGAL OFF CACHE BOOL "")
set(GLEW_OSMESA OFF CACHE BOOL "")
add_subdirectory(Libraries/glew/build/cmake)

add_subdirectory(Libraries/SDL)
#add_subdirectory(Libraries/zlib)

configure_file(CMake/Defines.hpp.in Injector/Defines.hpp)

add_library(InjectorEngine STATIC
	Source/Exception/CastException.cpp
	Source/Exception/Exception.cpp
	Source/Exception/NotImplementedException.cpp
	Source/Exception/NullException.cpp
	Source/Exception/OutOfRangeException.cpp

	Source/Graphics/Buffer.cpp
	Source/Graphics/CameraComponent.cpp
	Source/Graphics/CameraSystem.cpp
	Source/Graphics/ColorPipeline.cpp
	Source/Graphics/DiffusePipeline.cpp
	Source/Graphics/FlyTransformSystem.cpp
	Source/Graphics/GlBuffer.cpp
	Source/Graphics/GlCameraSystem.cpp
	Source/Graphics/GlColColorPipeline.cpp
	Source/Graphics/GlColorPipeline.cpp
	Source/Graphics/GlDiffusePipeline.cpp
	Source/Graphics/GlMesh.cpp
	Source/Graphics/GlPipeline.cpp
	Source/Graphics/GlRenderSystem.cpp
	Source/Graphics/GlShader.cpp
	Source/Graphics/GlTexDiffusePipeline.cpp
	Source/Graphics/GlTexture.cpp
	Source/Graphics/GlWindow.cpp
	Source/Graphics/Image.cpp
	Source/Graphics/Mesh.cpp
	Source/Graphics/Pipeline.cpp
	Source/Graphics/Primitive.cpp
	Source/Graphics/RenderComponent.cpp
	Source/Graphics/RenderSystem.cpp
	Source/Graphics/TexDiffusePipeline.cpp
	Source/Graphics/Texture.cpp
	Source/Graphics/VkBuffer.cpp
	Source/Graphics/VkCameraSystem.cpp
	Source/Graphics/VkColorPipeline.cpp
	Source/Graphics/VkDiffusePipeline.cpp
	Source/Graphics/VkMesh.cpp
	Source/Graphics/VkPipeline.cpp
	Source/Graphics/VkRenderSystem.cpp
	Source/Graphics/VkShader.cpp
	Source/Graphics/VkSwapchainData.cpp
	Source/Graphics/VkTexture.cpp
	Source/Graphics/VkWindow.cpp
	Source/Graphics/Window.cpp

	Source/Mathematics/AttachComponent.cpp
	Source/Mathematics/Converter.cpp
	Source/Mathematics/IntVector2.cpp
	Source/Mathematics/IntVector3.cpp
	Source/Mathematics/IntVector4.cpp
	Source/Mathematics/Matrix2.cpp
	Source/Mathematics/Matrix3.cpp
	Source/Mathematics/Matrix4.cpp
	Source/Mathematics/Quaternion.cpp
	Source/Mathematics/RotateComponent.cpp
	Source/Mathematics/SizeVector2.cpp
	Source/Mathematics/SizeVector3.cpp
	Source/Mathematics/SizeVector4.cpp
	Source/Mathematics/TransformComponent.cpp
	Source/Mathematics/TransformSystem.cpp
	Source/Mathematics/TranslateComponent.cpp
	Source/Mathematics/Vector2.cpp
	Source/Mathematics/Vector3.cpp
	Source/Mathematics/Vector4.cpp

	Source/Memory/ByteSwap.cpp
	Source/Memory/MemoryStream.cpp

	Source/Network/Datagram.cpp
	Source/Network/NetContextSystem.cpp

	Source/Storage/FileStream.cpp

	Source/Component.cpp
	Source/Engine.cpp
	Source/Entity.cpp
	Source/Manager.cpp
	Source/System.cpp
)
target_link_libraries(InjectorEngine PUBLIC
	asio
	glew_s
	SDL2main
	SDL2-static
	stb
	VulkanMemoryAllocator
	Vulkan::Vulkan
	#zlibstatic
)
target_include_directories(InjectorEngine PUBLIC
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/Include
	${PROJECT_SOURCE_DIR}/Libraries/glew/include
	${Vulkan_INCLUDE_DIRS}
	#${PROJECT_SOURCE_DIR}/Libraries/zlib
	#${PROJECT_BINARY_DIR}/Libraries/zlib
)

if(INJECTOR_BUILD_EDITOR)
	add_executable(InjectorEditor
	    Source/Editor.cpp
	)
	target_link_libraries(InjectorEditor PUBLIC 
	    InjectorEngine
	)
	target_include_directories(InjectorEditor PUBLIC
		${PROJECT_BINARY_DIR}
		${PROJECT_SOURCE_DIR}/Include
	)
endif()

set(INJECTOR_RESOURCES
	Images/GrayBox.png

	Shaders/Color.frag
	Shaders/Color.vert
	Shaders/Diffuse.frag
	Shaders/Diffuse.vert

	Shaders/Color.frag.spv
	Shaders/Color.vert.spv
	Shaders/Diffuse.frag.spv
	Shaders/Diffuse.vert.spv
)

foreach(FILE ${INJECTOR_RESOURCES})
    configure_file(Resources/${FILE} Resources/${FILE} COPYONLY)
endforeach(FILE)
