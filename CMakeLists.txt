cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(njng
	VERSION 0.1.0
	LANGUAGES CXX
)

#option(BUILD_SHARED_LIBS "Build shared libraries" OFF) TODO:
option(NJNG_INSTALL "Generate installation target" ON)

include(GNUInstallDirs)

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
set(BGFX_OPENGL_VERSION "" CACHE STRING "")

#set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "")
#set(ENTITYX_RUN_BENCHMARKS OFF CACHE BOOL "")
#set(ENTITYX_MAX_COMPONENTS 64 CACHE STRING "")
#set(ENTITYX_DT_TYPE double CACHE STRING "")
#set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL ON CACHE BOOL "")
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "")

add_subdirectory(3rdparty/bgfx.cmake)
add_subdirectory(3rdparty/entityx)
add_subdirectory(3rdparty/glfw)

configure_file(cmake/config.hpp.in njng/config.hpp)

add_library(njng INTERFACE)

target_link_libraries(njng INTERFACE
	bgfx
	entityx
	glfw
	dear-imgui
)

target_include_directories(njng INTERFACE
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
)
