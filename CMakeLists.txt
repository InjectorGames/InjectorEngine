cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

project(InjectorEngine
	VERSION 1.0.0
	LANGUAGES CXX
)

option(INJECTOR_BUILD_EDITOR "Build in editor executable" ON)

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
#add_subdirectory(3rdparty/zlib)

configure_file(cmake/defines.hpp.in injector/defines.hpp)

add_library(InjectorEngine STATIC
	source/engine.cpp
	source/int_vector2.cpp
	source/int_vector3.cpp
	source/int_vector4.cpp
	source/manager.cpp
	source/system.cpp
	source/vector2.cpp
	source/vector3.cpp
	source/vector4.cpp
	source/window.cpp
	source/window_system.cpp
)
target_link_libraries(InjectorEngine PUBLIC
	asio
	glew_s
	glm::glm
	SDL2main
	SDL2-static
	#zlibstatic
)
target_include_directories(InjectorEngine PUBLIC
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/3rdparty/glew/include
	#${PROJECT_SOURCE_DIR}/3rdparty/zlib
	#${PROJECT_BINARY_DIR}/3rdparty/zlib
)

if(INJECTOR_BUILD_EDITOR)
	add_executable(InjectorEditor
	    source/editor.cpp
	)
	target_link_libraries(InjectorEditor PUBLIC 
	    InjectorEngine
	)
	target_include_directories(InjectorEditor PUBLIC
		${PROJECT_BINARY_DIR}
		${PROJECT_SOURCE_DIR}/include
	)
endif()

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
