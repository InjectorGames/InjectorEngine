cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there.")
endif()

project(InjectorEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/entt)
add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# You can download SDK from https://vulkan.lunarg.com
find_package(Vulkan)

# TODO: FindLua, FindLibLZMA, FindGLUT

set(InjectorEngine_SOURCE
	source/engine.cpp
	source/main.cpp 
    source/shader.cpp
	source/system.cpp
	source/window.cpp

	source/opengl/gl_shader.cpp
	source/opengl/gl_window.cpp

	source/opengles/gles_shader.cpp
	source/opengles/gles_window.cpp
)

set(InjectorEngine_LIBRARIES
	EnTT::EnTT
	glad
	glfw
	glm::glm
)

set(InjectorEngine_INCLUDE_DIRS
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${ENTT_SOURCE_DIR}/single_include
	${GLAD_SOURCE_DIR}/include
	${GLFW_SOURCE_DIR}/include
)

set(InjectorEngine_RESOURCES
	LICENSE.md

	shaders/color.vert
)

if(${Vulkan_FOUND})
	list(APPEND InjectorEngine_SOURCE
		source/vulkan/vulkan.cpp
		source/vulkan/vk_shader.cpp
		source/vulkan/vk_window.cpp
	)

	list(APPEND InjectorEngine_LIBRARIES
		Vulkan::Vulkan
	)

	list(APPEND InjectorEngine_INCLUDE_DIRS
		${Vulkan_INCLUDE_DIRS}
	)

	list(APPEND InjectorEngine_RESOURCES
		shaders/dev.vert.spv
		shaders/dev.frag.spv
	)
endif()

configure_file(cmake/injector_engine_config.hpp.in injector_engine_config.hpp)

add_library(InjectorEngine STATIC ${InjectorEngine_SOURCE})
target_link_libraries(InjectorEngine PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(InjectorEngine PUBLIC ${InjectorEngine_INCLUDE_DIRS})

add_executable(InjectorEngineEditor ${InjectorEngine_SOURCE})
target_link_libraries(InjectorEngineEditor PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(InjectorEngineEditor PUBLIC ${InjectorEngine_INCLUDE_DIRS})

foreach(FILE ${InjectorEngine_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
