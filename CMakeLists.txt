cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there.")
endif()

project(InjectorEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/entityx)
add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# You can download SDK from https://vulkan.lunarg.com
find_package(Vulkan)

# TODO: FindLua, FindLibLZMA, FindGLUT

set(InjectorEngine_LIBRARIES
	entityx
	glad
	glfw
	glm::glm
)

set(InjectorEngine_INCLUDE_DIRS
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${ENTITYX_SOURCE_DIR}/entityx
	${GLAD_SOURCE_DIR}/include
	${GLFW_SOURCE_DIR}/include
)

set(InjectorEngine_RESOURCES
	LICENSE.md

	shaders/color.frag
	shaders/color.vert
	shaders/es_color.frag
	shaders/es_color.vert
)

if(${Vulkan_FOUND})
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

configure_file(cmake/config.hpp.in injector_engine/config.hpp)

add_executable(InjectorEngineEditor
	source/main.cpp
)
target_link_libraries(InjectorEngineEditor PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(InjectorEngineEditor PUBLIC ${InjectorEngine_INCLUDE_DIRS})

foreach(FILE ${InjectorEngine_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
