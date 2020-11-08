project(VulkanMemoryAllocator LANGUAGES CXX)

add_library(VulkanMemoryAllocator INTERFACE)

target_include_directories(VulkanMemoryAllocator INTERFACE
    ${PROJECT_SOURCE_DIR}/Libraries/VulkanMemoryAllocator/src)
