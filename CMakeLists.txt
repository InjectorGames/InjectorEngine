cmake_minimum_required(VERSION 3.10)

project(InjectorEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# You can download SDK from https://vulkan.lunarg.com
find_package(Vulkan REQUIRED)

set(InjectorEngine_SOURCE
	source/engine.cpp
)

set(InjectorEngine_LIBRARIES
	Vulkan::Vulkan
)

set(InjectorEngine_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	${Vulkan_INCLUDE_DIRS}
)

set(InjectorEngine_RESOURCES
	LICENSE.md
PARENT_SCOPE)

add_library(${PROJECT_NAME} STATIC ${InjectorEngine_SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC ${InjectorEngine_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${InjectorEngine_INCLUDE_DIRS})

foreach(FILE ${InjectorEngine_RESOURCES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)
