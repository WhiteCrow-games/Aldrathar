cmake_minimum_required(VERSION 3.16)

project(Aldrathar VERSION 0.0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin
)

find_package(SFML 3 REQUIRED COMPONENTS
    Graphics
    Window
    System
)

file(GLOB SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Aldrathar
    ${SOURCES}
)

target_include_directories(Aldrathar
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Aldrathar
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)
