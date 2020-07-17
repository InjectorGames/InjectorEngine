cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(injector-engine
	VERSION 1.0.0
	LANGUAGES CXX
)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/asio.cmake)

set(BUILD_UTILS OFF CACHE BOOL "")
set(GLEW_REGAL OFF CACHE BOOL "")
set(GLEW_OSMESA OFF CACHE BOOL "")
add_subdirectory(3rdparty/glew/build/cmake)

add_subdirectory(3rdparty/glm)
add_subdirectory(3rdparty/sdl)
add_subdirectory(3rdparty/zlib)

configure_file(cmake/defines.hpp.in injector/defines.hpp)

add_library(injector-engine STATIC
	${PROJECT_SOURCE_DIR}/source/component.cpp
	${PROJECT_SOURCE_DIR}/source/entity.cpp
	${PROJECT_SOURCE_DIR}/source/manager.cpp
	${PROJECT_SOURCE_DIR}/source/system.cpp
)
target_link_libraries(injector-engine PUBLIC
	asio
	glew_s
	glm::glm
	SDL2main
	SDL2-static
	zlibstatic
)
target_include_directories(injector-engine PUBLIC
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/3rdparty/glew/include
	${PROJECT_SOURCE_DIR}/3rdparty/zlib
	${PROJECT_BINARY_DIR}/3rdparty/zlib
)

set(INJECTOR_RESOURCES
	shaders/col_color.frag
	shaders/col_color.vert
	shaders/color.frag
	shaders/color.vert
	shaders/diffuse.frag
	shaders/diffuse.vert
	shaders/gradient_sky.frag
	shaders/gradient_sky.vert
)

foreach(FILE ${INJECTOR_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
