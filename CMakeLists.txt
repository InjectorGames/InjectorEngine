cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(inject
	VERSION 1.0.0
	LANGUAGES CXX
)

option(INJECT_BUILD_EDITOR "Build editor executable" ON)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/asio.cmake)

set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "")
set(ENTITYX_RUN_BENCHMARKS OFF CACHE BOOL "")
set(ENTITYX_MAX_COMPONENTS 64 CACHE STRING "")
set(ENTITYX_DT_TYPE float CACHE STRING "")
set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "")
add_subdirectory(3rdparty/entityx)

set(BUILD_UTILS OFF CACHE BOOL "")
set(GLEW_REGAL OFF CACHE BOOL "")
set(GLEW_OSMESA OFF CACHE BOOL "")
add_subdirectory(3rdparty/glew/build/cmake)

add_subdirectory(3rdparty/glm)
add_subdirectory(3rdparty/sdl)

configure_file(cmake/config.hpp.in inject/config.hpp)

add_library(inject INTERFACE
)
target_link_libraries(inject INTERFACE
	asio
	entityx
	glew_s
	glm::glm
	SDL2main
	SDL2-static
)
target_include_directories(inject INTERFACE
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/3rdparty/glew/include
)

if(INJECT_BUILD_EDITOR)
	add_executable(main
	    ${PROJECT_SOURCE_DIR}/source/main.cpp
	)
	target_link_libraries(main PUBLIC 
	    inject
	)
	target_include_directories(main PUBLIC
		${PROJECT_SOURCE_DIR}/include
	)
endif()

set(INJECT_RESOURCES
	shaders/color.vert
	shaders/color.frag
	shaders/diffuse.vert
	shaders/diffuse.frag
	shaders/gradient_sky.vert
	shaders/gradient_sky.frag
)

foreach(FILE ${INJECT_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
