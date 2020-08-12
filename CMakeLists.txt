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

include(TestBigEndian)
TEST_BIG_ENDIAN(INJECTOR_BIG_ENDIAN)

include(FindVulkan)
include(cmake/asio.cmake)
include(cmake/vma.cmake)

set(BUILD_UTILS OFF CACHE BOOL "")
set(GLEW_REGAL OFF CACHE BOOL "")
set(GLEW_OSMESA OFF CACHE BOOL "")
add_subdirectory(3rdparty/glew/build/cmake)

add_subdirectory(3rdparty/glm)
add_subdirectory(3rdparty/sdl)
#add_subdirectory(3rdparty/zlib)

configure_file(cmake/defines.hpp.in injector/defines.hpp)

add_library(InjectorEngine STATIC
	source/graphics/buffer.cpp
	source/graphics/gl_attribute.cpp
	source/graphics/gl_buffer.cpp
	source/graphics/gl_color_material.cpp
	source/graphics/gl_material.cpp
	source/graphics/gl_mesh.cpp
	source/graphics/gl_shader.cpp
	source/graphics/gl_window.cpp
	source/graphics/image.cpp
	source/graphics/material.cpp
	source/graphics/mesh.cpp
	source/graphics/primitive.cpp
	source/graphics/render_component.cpp
	source/graphics/render_system.cpp
	source/graphics/shader.cpp
	source/graphics/vk_buffer.cpp
	source/graphics/vk_mesh.cpp
	source/graphics/vk_render_system.cpp
	source/graphics/vk_shader.cpp
	source/graphics/vk_window.cpp
	source/graphics/window.cpp

	source/mathematics/camera_component.cpp
	source/mathematics/camera_system.cpp
	source/mathematics/converter.cpp
	source/mathematics/int_vector2.cpp
	source/mathematics/int_vector3.cpp
	source/mathematics/int_vector4.cpp
	source/mathematics/matrix2.cpp
	source/mathematics/matrix3.cpp
	source/mathematics/matrix4.cpp
	source/mathematics/quaternion.cpp
	source/mathematics/rotate_component.cpp
	source/mathematics/transform_component.cpp
	source/mathematics/transform_system.cpp
	source/mathematics/translate_component.cpp
	source/mathematics/vector2.cpp
	source/mathematics/vector3.cpp
	source/mathematics/vector4.cpp

	source/byte_swap.cpp
	source/component.cpp
	source/engine.cpp
	source/entity.cpp
	source/file_stream.cpp
	source/manager.cpp
	source/system.cpp
)
target_link_libraries(InjectorEngine PUBLIC
	asio
	glew_s
	glm::glm
	SDL2main
	SDL2-static
	vma
	Vulkan::Vulkan
	#zlibstatic
)
target_include_directories(InjectorEngine PUBLIC
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/3rdparty/glew/include
	${Vulkan_INCLUDE_DIRS}
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
	shaders/opengl/col_color.frag
	shaders/opengl/col_color.vert
	shaders/opengl/color.frag
	shaders/opengl/color.vert
	shaders/opengl/diffuse.frag
	shaders/opengl/diffuse.vert
	shaders/opengl/gradient_sky.frag
	shaders/opengl/gradient_sky.vert

	shaders/vulkan/tutorial.vert.spv
	shaders/vulkan/tutorial.frag.spv
)

foreach(FILE ${INJECTOR_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
