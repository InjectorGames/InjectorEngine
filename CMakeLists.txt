cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there.")
endif()

project(InjectorEngine
	VERSION 0.1.0
	LANGUAGES CXX
	DESCRIPTION "C++ Game/Program engine"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BGFX_BUILD_TOOLS ON CACHE BOOL "")
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "")
set(BGFX_INSTALL ON CACHE BOOL "")
set(BGFX_INSTALL_EXAMPLES OFF CACHE BOOL "")
set(BGFX_CUSTOM_TARGETS ON CACHE BOOL "")
set(BGFX_USE_OVR OFF CACHE BOOL "") # wtf is this?
set(BGFX_AMALGAMATED OFF CACHE BOOL "")
set(BX_AMALGAMATED OFF CACHE BOOL "")
set(BGFX_CONFIG_DEBUG OFF CACHE BOOL "")
set(BGFX_USE_DEBUG_SUFFIX ON CACHE BOOL "")
set(BGFX_OPENGL_VERSION "3.3" CACHE STRING "")

set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "")
set(ENTITYX_RUN_BENCHMARKS OFF CACHE BOOL "")
set(ENTITYX_MAX_COMPONENTS 64 CACHE STRING "")
set(ENTITYX_DT_TYPE double CACHE STRING "")
set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "")

set(FN_SET_c0rp3n_CXX_FLAGS OFF CACHE BOOL "")
set(FN_COMPILE_SSE2 ON CACHE BOOL "")
set(FN_COMPILE_SSE41 ON CACHE BOOL "")
set(FN_COMPILE_AVX2 ON CACHE BOOL "")
set(FN_COMPILE_AVX512 OFF CACHE BOOL "")
set(FN_USE_FMA ON CACHE BOOL "")
set(FN_ALIGNED_SETS ON CACHE BOOL "")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL ON CACHE BOOL "")
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "")

include(GNUInstallDirs)
include(CMakeDependentOption)

add_subdirectory(external/bgfx.cmake)
add_subdirectory(external/entityx)
add_subdirectory(external/FastNoiseSIMD)
add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# You can download SDK from https://vulkan.lunarg.com
find_package(Vulkan)

# TODO: FindLua, FindLibLZMA, FindGLUT

set(InjectorEngine_LIBRARIES
	bgfx
	entityx
	FastNoiseSIMD
	glad
	glfw
	glm::glm
)

set(InjectorEngine_INCLUDE_DIRS
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${GLAD_SOURCE_DIR}/include
)

set(InjectorEngine_RESOURCES
	LICENSE.txt

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
