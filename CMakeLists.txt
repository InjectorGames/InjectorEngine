cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(inject
	VERSION 0.1.0
	LANGUAGES CXX
)

#option(BUILD_SHARED_LIBS "Build shared libraries" OFF) TODO:
#option(NJNG_INSTALL "Generate installation target" ON)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "")
set(ENTITYX_RUN_BENCHMARKS OFF CACHE BOOL "")
set(ENTITYX_MAX_COMPONENTS 64 CACHE STRING "")
set(ENTITYX_DT_TYPE double CACHE STRING "")
set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "")

set(BUILD_UTILS OFF CACHE BOOL "")
set(GLEW_REGAL OFF CACHE BOOL "")
set(GLEW_OSMESA OFF CACHE BOOL "")

include(cmake/asio.cmake)
add_subdirectory(3rdparty/entityx)
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

add_executable(main
    ${PROJECT_SOURCE_DIR}/source/main.cpp
)
target_link_libraries(main PUBLIC 
    inject
)
target_include_directories(main PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

set(INJECT_RESOURCES
	shaders/color.vert
	shaders/color.frag
)

foreach(FILE ${INJECT_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
