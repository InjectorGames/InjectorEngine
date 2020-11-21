cmake_minimum_required(VERSION 3.10)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif ()

project(InjectorEngine
    VERSION 0.1.0
    LANGUAGES CXX)

option(INJECTOR_BUILD_EDITOR "Build editor executable" ON)
option(INJECTOR_BUILD_VIRTUAL_REALITY "Build with virtual reality support" ON)

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
    set(INJECTOR_SYSTEM_MACOS 0)
    set(INJECTOR_SYSTEM_WINDOWS 0)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_MACOS 1)
    set(INJECTOR_SYSTEM_WINDOWS 0)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(INJECTOR_SYSTEM_LINUX 0)
    set(INJECTOR_SYSTEM_MACOS 0)
    set(INJECTOR_SYSTEM_WINDOWS 1)
else ()
    message(FATAL_ERROR "Failed to detect system name")
endif ()

if (INJECTOR_BUILD_VIRTUAL_REALITY AND (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows"))
    set(INJECTOR_SUPPORT_VIRTUAL_REALITY 1)
else ()
    set(INJECTOR_SUPPORT_VIRTUAL_REALITY 0)
endif ()

configure_file(CMake/Defines.hpp.in Injector/Defines.hpp)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/assimp)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl@1.1/1.1.1h CACHE FILEPATH "" FORCE)
    set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.dylib CACHE FILEPATH "" FORCE)
    set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib CACHE FILEPATH "" FORCE)
endif ()

find_package(Vulkan REQUIRED)
find_package(OpenSSL REQUIRED)

include(CMake/stb.cmake)
include(CMake/VulkanMemoryAllocator.cmake)
set(IMGUI_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Libraries/imgui)

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

if (INJECTOR_SUPPORT_VIRTUAL_REALITY)
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
    Libraries/imgui/imgui_demo.cpp
    Libraries/imgui/imgui_draw.cpp
    Libraries/imgui/imgui_widgets.cpp
    Libraries/imgui/imgui.cpp
    Libraries/imgui/examples/imgui_impl_glfw.cpp

    Source/ECS/EcsEntity.cpp
    Source/ECS/EcsManager.cpp

    Source/Exception/CastException.cpp
    Source/Exception/Exception.cpp
    Source/Exception/NullException.cpp
    Source/Exception/OutOfRangeException.cpp

    Source/Graphics/GUI/EditorGuiHandler.cpp

    Source/Graphics/OpenGL/Pipeline/GlColorColorGpuPipeline.cpp
    Source/Graphics/OpenGL/Pipeline/GlColorGpuPipeline.cpp
    Source/Graphics/OpenGL/Pipeline/GlDiffuseGpuPipeline.cpp
    Source/Graphics/OpenGL/Pipeline/GlGuiGpuPipeline.cpp
    Source/Graphics/OpenGL/Pipeline/GlImageDiffuseGpuPipeline.cpp
    Source/Graphics/OpenGL/Pipeline/GlSimulatedSkyGpuPipeline.cpp

    Source/Graphics/OpenGL/GlGpuBuffer.cpp
    Source/Graphics/OpenGL/GlGpuFramebuffer.cpp
    Source/Graphics/OpenGL/GlGpuShader.cpp
    Source/Graphics/OpenGL/GlGpuImage.cpp
    Source/Graphics/OpenGL/GlGpuMesh.cpp
    Source/Graphics/OpenGL/GlGpuPipeline.cpp
    Source/Graphics/OpenGL/GlGpuShader.cpp
    Source/Graphics/OpenGL/GlGpuWindow.cpp
    Source/Graphics/OpenGL/GlRenderEcsSystem.cpp

    Source/Graphics/Vulkan/Pipeline/VkColorGpuPipeline.cpp
    Source/Graphics/Vulkan/Pipeline/VkDiffuseGpuPipeline.cpp
    Source/Graphics/Vulkan/Pipeline/VkImageDiffuseGpuPipeline.cpp

    Source/Graphics/Vulkan/VkGpuBuffer.cpp
    Source/Graphics/Vulkan/VkGpuImage.cpp
    Source/Graphics/Vulkan/VkGpuMesh.cpp
    Source/Graphics/Vulkan/VkGpuPipeline.cpp
    Source/Graphics/Vulkan/VkGpuShader.cpp
    Source/Graphics/Vulkan/VkGpuSwapchain.cpp
    Source/Graphics/Vulkan/VkGpuWindow.cpp
    Source/Graphics/Vulkan/VkRenderEcsSystem.cpp
    Source/Graphics/Vulkan/VkSwapchainData.cpp

    Source/Graphics/AspectRatioEcsSystem.cpp
    Source/Graphics/CameraEcsComponent.cpp
    Source/Graphics/CameraEcsSystem.cpp
    Source/Graphics/FreeCameraEcsSystem.cpp
    Source/Graphics/GpuBuffer.cpp
    Source/Graphics/GpuFramebuffer.cpp
    Source/Graphics/GpuImage.cpp
    Source/Graphics/GpuMesh.cpp
    Source/Graphics/GpuPipeline.cpp
    Source/Graphics/GpuShader.cpp
    Source/Graphics/GpuWindow.cpp
    Source/Graphics/GuiEcsComponent.cpp
    Source/Graphics/GuiEcsSystem.cpp
    Source/Graphics/ImageData.cpp
    Source/Graphics/ModelData.cpp
    Source/Graphics/RenderEcsComponent.cpp
    Source/Graphics/RenderEcsSystem.cpp
    Source/Graphics/ShaderData.cpp
    Source/Graphics/SimSkyEcsSystem.cpp
    Source/Graphics/VirtualRealityEcsSystem.cpp

    Source/Mathematics/Angle.cpp
    Source/Mathematics/BoundingBox2.cpp
    Source/Mathematics/BoundingBox3.cpp
    Source/Mathematics/BoundingSphere2.cpp
    Source/Mathematics/BoundingSphere3.cpp
    Source/Mathematics/Color.cpp
    Source/Mathematics/Quaternion.cpp
    Source/Mathematics/RotateEcsComponent.cpp
    Source/Mathematics/TransformEcsComponent.cpp
    Source/Mathematics/TransformEcsSystem.cpp
    Source/Mathematics/TranslateEcsComponent.cpp

    Source/Network/ClientSocket.cpp
    Source/Network/ClientSocketEcsSystem.cpp
    Source/Network/Datagram.cpp
    Source/Network/Endpoint.cpp
    Source/Network/Socket.cpp
    Source/Network/TcpServerSocket.cpp
    Source/Network/TcpSessionSocket.cpp

    Source/Storage/FileStream.cpp

    Source/ByteSwap.cpp
    Source/Compressor.cpp
    Source/Engine.cpp)
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
    ${IMGUI_INCLUDE_DIRS}
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
    Fonts/JetBrainsMonoBold.ttf
    Fonts/JetBrainsMonoBoldItalic.ttf
    Fonts/JetBrainsMonoItalic.ttf
    Fonts/JetBrainsMonoRegular.ttf
    Fonts/RobotoBold.ttf
    Fonts/RobotoBoldItalic.ttf
    Fonts/RobotoItalic.ttf
    Fonts/RobotoRegular.ttf

    Images/GrayBox.png
    Images/Logo16.png
    Images/Logo32.png
    Images/Logo48.png

    Models/UtahTeapot.fbx

    Shaders/Color.frag
    Shaders/Color.vert
    Shaders/ColorColor.frag
    Shaders/ColorColor.vert
    Shaders/SimulatedSky.vert
    Shaders/SimulatedSky.frag
    Shaders/Diffuse.frag
    Shaders/Diffuse.vert
    Shaders/Gui.vert
    Shaders/Gui.frag
    Shaders/ImageDiffuse.frag
    Shaders/ImageDiffuse.vert

    Shaders/Color.frag.spv
    Shaders/Color.vert.spv
    Shaders/ColorColor.frag.spv
    Shaders/ColorColor.vert.spv
    Shaders/Diffuse.frag.spv
    Shaders/Diffuse.vert.spv
    Shaders/ImageDiffuse.frag.spv
    Shaders/ImageDiffuse.vert.spv)

foreach (FILE ${INJECTOR_RESOURCES})
    configure_file(Resources/${FILE} Resources/${FILE} COPYONLY)
endforeach (FILE)
