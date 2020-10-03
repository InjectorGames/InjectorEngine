cmake_minimum_required(VERSION 3.10)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif ()

project(InjectorEngine
    VERSION 1.0.0
    LANGUAGES CXX)

option(INJECTOR_BUILD_EDITOR "Build editor executable" ON)
option(INJECTOR_BUILD_VR "Build with virtual reality support" ON)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

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

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(INJECTOR_SYSTEM_LINUX 1)
    set(INJECTOR_SYSTEM_WINDOWS 0)
    set(INJECTOR_SYSTEM_MACOS 0)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_WINDOWS 1)
    set(INJECTOR_SYSTEM_MACOS 0)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_WINDOWS 0)
    set(INJECTOR_SYSTEM_MACOS 1)
else ()
    message(FATAL_ERROR "Failed to detect system name")
endif ()

if (INJECTOR_BUILD_VR AND (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows"))
    set(INJECTOR_SUPPORT_VR 1)
else ()
    set(INJECTOR_SUPPORT_VR 0)
endif ()

configure_file(CMake/Defines.hpp.in Injector/Defines.hpp)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/assimp)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl@1.1/1.1.1g)
    set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.dylib CACHE FILEPATH "" FORCE)
    set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib CACHE FILEPATH "" FORCE)
endif ()

find_package(Vulkan REQUIRED)
find_package(OpenSSL REQUIRED)

include(CMake/stb.cmake)
include(CMake/VulkanMemoryAllocator.cmake)

add_subdirectory(Libraries/glew/build/cmake)
set(GLEW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Libraries/glew/include)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/glfw)

set(LZ4_BUILD_LEGACY_LZ4C OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/lz4/build/cmake)
set(LZ4_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Libraries/lz4/lib)

if (INJECTOR_SUPPORT_VR)
    add_subdirectory(Libraries/openvr)

    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        if (CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(OPENVR_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries/openvr/lib/linux32/libopenvr_api.so)
            configure_file(${PROJECT_SOURCE_DIR}/Libraries/openvr/bin/linux32/libopenvr_api.so libopenvr_api.so COPYONLY)
        elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(OPENVR_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries/openvr/lib/linux64/libopenvr_api.so)
            configure_file(${PROJECT_SOURCE_DIR}/Libraries/openvr/bin/linux64/libopenvr_api.so libopenvr_api.so COPYONLY)
        endif ()
    elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
        if (CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(OPENVR_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries/openvr/lib/win32/openvr_api.lib)
            configure_file(${PROJECT_SOURCE_DIR}/Libraries/openvr/bin/win32/openvr_api.dll openvr_api.dll COPYONLY)
        elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(OPENVR_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries/openvr/lib/win64/openvr_api.lib)
            configure_file(${PROJECT_SOURCE_DIR}/Libraries/openvr/bin/win64/openvr_api.dll openvr_api.dll COPYONLY)
        endif ()
    endif ()

    add_library(openvr STATIC IMPORTED)
    set_target_properties(openvr PROPERTIES IMPORTED_LOCATION ${OPENVR_LIBRARY_DIR})

    set(OPENVR_LINK_LIB openvr)
    set(OPENVR_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Libraries/openvr/headers)
endif ()

add_library(InjectorEngine STATIC
    Source/Exception/CastException.cpp
    Source/Exception/Exception.cpp
    Source/Exception/NullException.cpp
    Source/Exception/OutOfRangeException.cpp

    Source/Graphics/Pipeline/GlColorColorGpuPipeline.cpp
    Source/Graphics/Pipeline/GlColorGpuPipeline.cpp
    Source/Graphics/Pipeline/GlDiffuseGpuPipeline.cpp
    Source/Graphics/Pipeline/GlGpuPipeline.cpp
    Source/Graphics/Pipeline/GlSimulatedSkyGpuPipeline.cpp
    Source/Graphics/Pipeline/GlTextureDiffuseGpuPipeline.cpp
    Source/Graphics/Pipeline/VkColorGpuPipeline.cpp
    Source/Graphics/Pipeline/VkDiffuseGpuPipeline.cpp
    Source/Graphics/Pipeline/VkGpuPipeline.cpp

    Source/Graphics/CameraComponent.cpp
    Source/Graphics/CameraSystem.cpp
    Source/Graphics/FreeCameraSystem.cpp
    Source/Graphics/GlCameraSystem.cpp
    Source/Graphics/GlGpuBuffer.cpp
    Source/Graphics/GlGpuFramebuffer.cpp
    Source/Graphics/GlGpuShader.cpp
    Source/Graphics/GlGpuImage.cpp
    Source/Graphics/GlGpuMesh.cpp
    Source/Graphics/GlGpuShader.cpp
    Source/Graphics/GlRenderSystem.cpp
    Source/Graphics/GlWindow.cpp
    Source/Graphics/GpuBuffer.cpp
    Source/Graphics/GpuFramebuffer.cpp
    Source/Graphics/GpuImage.cpp
    Source/Graphics/GpuMesh.cpp
    Source/Graphics/GpuShader.cpp
    Source/Graphics/GuiComponent.cpp
    Source/Graphics/GuiSystem.cpp
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
    Source/Graphics/VrSystem.cpp
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

    Source/Network/ConsoleSystem.cpp
    Source/Network/Endpoint.cpp
    Source/Network/Socket.cpp

    Source/Storage/FileStream.cpp

    Source/Compressor.cpp
    Source/Engine.cpp
    Source/Entity.cpp
    Source/Manager.cpp)
target_link_libraries(InjectorEngine PUBLIC
    assimp
    glew_s
    glfw
    lz4_static
    OpenSSL::SSL
    OpenSSL::Crypto
    ${OPENVR_LINK_LIB}
    stb
    VulkanMemoryAllocator
    Vulkan::Vulkan)
target_include_directories(InjectorEngine PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/Include
    ${GLEW_INCLUDE_DIRS}
    ${LZ4_INCLUDE_DIRS}
    ${OPENVR_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIRS})

if (INJECTOR_BUILD_EDITOR)
    add_executable(InjectorEditor
        Source/Editor.cpp)
    target_link_libraries(InjectorEditor PRIVATE
        InjectorEngine)
    target_include_directories(InjectorEditor PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/Include)
endif ()

set(INJECTOR_RESOURCES
    Images/GrayBox.png
    Images/Logo16.png
    Images/Logo32.png
    Images/Logo48.png

    Models/UtahTeapot.fbx

    Shaders/ColorColor.frag
    Shaders/ColorColor.vert
    Shaders/Color.frag
    Shaders/Color.vert
    Shaders/SimulatedSky.vert
    Shaders/SimulatedSky.frag
    Shaders/Diffuse.frag
    Shaders/Diffuse.vert
    Shaders/TextureDiffuse.frag
    Shaders/TextureDiffuse.vert
    Shaders/Color.frag.spv
    Shaders/Color.vert.spv
    Shaders/Diffuse.frag.spv
    Shaders/Diffuse.vert.spv)

foreach (FILE ${INJECTOR_RESOURCES})
    configure_file(Resources/${FILE} Resources/${FILE} COPYONLY)
endforeach (FILE)
