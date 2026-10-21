cmake_minimum_required(VERSION 3.25)

project(Aldrathar
    VERSION 0.1.0
    DESCRIPTION "Aldrathar - Retro Survival Horror Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)
find_package(glm CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(Aldrathar
    src/main.cpp
    src/core/Engine.cpp
    src/game/Game.cpp
    src/game/CollisionWorld.cpp
    src/game/Player.cpp
    src/game/DragonEntity.cpp
    src/renderer/Renderer.cpp
)

target_include_directories(Aldrathar PRIVATE include)

target_link_libraries(Aldrathar PRIVATE
    PkgConfig::RAYLIB
    glm::glm
    nlohmann_json::nlohmann_json
)

target_compile_definitions(Aldrathar PRIVATE
    ALDRATHAR_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders"
)

target_compile_options(Aldrathar PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

message(STATUS "Aldrathar: C++20")
message(STATUS "Aldrathar: raylib")
message(STATUS "Aldrathar: GLM")
message(STATUS "Aldrathar: nlohmann-json")
