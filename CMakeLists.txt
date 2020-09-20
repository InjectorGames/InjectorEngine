cmake_minimum_required(VERSION 3.10)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif ()

project(InjectorEngine
        VERSION 1.0.0
        LANGUAGES CXX)

option(INJECTOR_BUILD_EDITOR "Build editor executable" ON)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(TestBigEndian)
TEST_BIG_ENDIAN(INJECTOR_BIG_ENDIAN)

set(INJECTOR_POINTER_SIZE ${CMAKE_SIZEOF_VOID_P})
set(INJECTOR_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set(INJECTOR_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(INJECTOR_SYSTEM_32 1)
    set(INJECTOR_SYSTEM_64 0)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(INJECTOR_SYSTEM_32 0)
    set(INJECTOR_SYSTEM_64 1)
else ()
    message(FATAL_ERROR "Failed to detect system architecture")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(INJECTOR_SYSTEM_LINUX 1)
    set(INJECTOR_SYSTEM_WINDOWS 0)
    set(INJECTOR_SYSTEM_MACOS 0)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_WINDOWS 1)
    set(INJECTOR_SYSTEM_MACOS 0)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_WINDOWS 0)
    set(INJECTOR_SYSTEM_MACOS 1)
else ()
    message(FATAL_ERROR "Failed to detect system name")
endif ()

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_INSTALL OFF CACHE BOOL "")
add_subdirectory(Libraries/assimp)

include(FindVulkan)
include(CMake/asio.cmake)
include(CMake/stb.cmake)
include(CMake/VulkanMemoryAllocator.cmake)

set(BUILD_UTILS OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_STATIC_LIBS ON CACHE BOOL "")

add_subdirectory(Libraries/glew/build/cmake)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "")
add_subdirectory(Libraries/glfw)

add_subdirectory(Libraries/lz4/build/cmake)

configure_file(CMake/Defines.hpp.in Injector/Defines.hpp)

add_library(InjectorEngine STATIC
        Source/Exception/CastException.cpp
        Source/Exception/Exception.cpp
        Source/Exception/NotImplementedException.cpp
        Source/Exception/NullException.cpp
        Source/Exception/OutOfRangeException.cpp

        Source/Graphics/Pipeline/ColorGpuPipeline.cpp
        Source/Graphics/Pipeline/DiffuseGpuPipeline.cpp
        Source/Graphics/Pipeline/GlColColorGpuPipeline.cpp
        Source/Graphics/Pipeline/GlColorGpuPipeline.cpp
        Source/Graphics/Pipeline/GlDiffuseGpuPipeline.cpp
        Source/Graphics/Pipeline/GlGpuPipeline.cpp
        Source/Graphics/Pipeline/GlSimSkyGpuPipeline.cpp
        Source/Graphics/Pipeline/GlTexDiffuseGpuPipeline.cpp
        Source/Graphics/Pipeline/GpuPipeline.cpp
        Source/Graphics/Pipeline/SimSkyGpuPipeline.cpp
        Source/Graphics/Pipeline/TexDiffuseGpuPipeline.cpp
        Source/Graphics/Pipeline/VkColorGpuPipeline.cpp
        Source/Graphics/Pipeline/VkDiffuseGpuPipeline.cpp
        Source/Graphics/Pipeline/VkGpuPipeline.cpp

        Source/Graphics/CameraComponent.cpp
        Source/Graphics/CameraSystem.cpp
        Source/Graphics/FlyTransformSystem.cpp
        Source/Graphics/GlCameraSystem.cpp
        Source/Graphics/GlGpuBuffer.cpp
        Source/Graphics/GlGpuShader.cpp
        Source/Graphics/GlGpuImage.cpp
        Source/Graphics/GlGpuMesh.cpp
        Source/Graphics/GlGpuShader.cpp
        Source/Graphics/GlRenderSystem.cpp
        Source/Graphics/GlWindow.cpp
        Source/Graphics/GpuBuffer.cpp
        Source/Graphics/GpuImage.cpp
        Source/Graphics/GpuMesh.cpp
        Source/Graphics/GpuShader.cpp
        Source/Graphics/ImageData.cpp
        Source/Graphics/ModelData.cpp
        Source/Graphics/RenderComponent.cpp
        Source/Graphics/RenderSystem.cpp
        Source/Graphics/ShaderData.cpp
        Source/Graphics/SimSkySystem.cpp
        Source/Graphics/VkCameraSystem.cpp
        Source/Graphics/VkGpuBuffer.cpp
        Source/Graphics/VkGpuImage.cpp
        Source/Graphics/VkGpuMesh.cpp
        Source/Graphics/VkGpuShader.cpp
        Source/Graphics/VkRenderSystem.cpp
        Source/Graphics/VkSwapchainData.cpp
        Source/Graphics/VkWindow.cpp
        Source/Graphics/Window.cpp

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
        Source/Compressor.cpp
        Source/Engine.cpp
        Source/Entity.cpp
        Source/Manager.cpp
        Source/System.cpp)
target_link_libraries(InjectorEngine PUBLIC
        asio
        assimp
        glew_s
        glfw
        lz4_static
        stb
        VulkanMemoryAllocator
        Vulkan::Vulkan)
target_include_directories(InjectorEngine PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/Include
        ${PROJECT_SOURCE_DIR}/Libraries/glew/include
        ${PROJECT_SOURCE_DIR}/Libraries/lz4/lib
        ${Vulkan_INCLUDE_DIRS})

if (INJECTOR_BUILD_EDITOR)
    add_executable(InjectorEditor
            Source/Editor.cpp)
    target_link_libraries(InjectorEditor PUBLIC
            InjectorEngine)
    target_include_directories(InjectorEditor PUBLIC
            ${PROJECT_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/Include)
endif ()

set(INJECTOR_RESOURCES
        Images/GrayBox.png
        Images/Logo16.png
        Images/Logo32.png
        Images/Logo48.png

        Models/UtahTeapot.fbx

        Shaders/ColColor.frag
        Shaders/ColColor.vert
        Shaders/Color.frag
        Shaders/Color.vert
        Shaders/SimSky.vert
        Shaders/SimSky.frag
        Shaders/Diffuse.frag
        Shaders/Diffuse.vert
        Shaders/TexDiffuse.frag
        Shaders/TexDiffuse.vert
        Shaders/Color.frag.spv
        Shaders/Color.vert.spv
        Shaders/Diffuse.frag.spv
        Shaders/Diffuse.vert.spv)

foreach (FILE ${INJECTOR_RESOURCES})
    configure_file(Resources/${FILE} Resources/${FILE} COPYONLY)
endforeach (FILE)
