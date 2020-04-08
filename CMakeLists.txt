cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there.")
endif()

project(InjectorEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/glfw)
add_subdirectory(external/entt)
add_subdirectory(external/glm)

# You can download SDK from https://vulkan.lunarg.com
find_package(Vulkan REQUIRED)

# TODO: FindLua, FindLibLZMA, FindGLUT

set(InjectorEngine_SOURCE
	source/engine.cpp
	source/main.cpp 
	source/opengl_window.cpp
    source/shader.cpp
	source/system.cpp
	source/vulkan.cpp
	source/vulkan_shader.cpp
	source/vulkan_window.cpp
	source/window.cpp
)

set(InjectorEngine_LIBRARIES
	glfw
	EnTT::EnTT
	glm::glm
	Vulkan::Vulkan
)

set(InjectorEngine_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	${GLFW_SOURCE_DIR}/include
	${ENTT_SOURCE_DIR}/single_include
	${Vulkan_INCLUDE_DIRS}
)

set(InjectorEngine_RESOURCES
	LICENSE.md

	shaders/dev.vert.spv
	shaders/dev.frag.spv
)

add_library(InjectorEngine STATIC ${InjectorEngine_SOURCE})
target_link_libraries(InjectorEngine PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(InjectorEngine PUBLIC ${InjectorEngine_INCLUDE_DIRS})

add_executable(InjectorEngineEditor ${InjectorEngine_SOURCE})
target_link_libraries(InjectorEngineEditor PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(InjectorEngineEditor PUBLIC ${InjectorEngine_INCLUDE_DIRS})

foreach(FILE ${InjectorEngine_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
