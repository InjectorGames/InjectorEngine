project(asio LANGUAGES CXX)

add_library(asio INTERFACE)

target_include_directories(asio INTERFACE
    ${PROJECT_SOURCE_DIR}/Libraries/asio/asio/include
)
