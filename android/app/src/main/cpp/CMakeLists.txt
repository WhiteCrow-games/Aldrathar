cmake_minimum_required(VERSION 3.22.1)

project(AldratharAndroid LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PLATFORM "Android" CACHE STRING "" FORCE)
set(OPENGL_VERSION "ES 2.0" CACHE STRING "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(WITH_PIC ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_library(main SHARED
    ../../../../../src/main.cpp
    ../../../../../src/core/Engine.cpp
    ../../../../../src/game/Game.cpp
    ../../../../../src/game/CollisionWorld.cpp
    ../../../../../src/game/Player.cpp
    ../../../../../src/game/DragonEntity.cpp
    ../../../../../src/renderer/Renderer.cpp
)

target_include_directories(main PRIVATE
    ../../../../../include
)

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(main PRIVATE
    raylib
    android
    log
    EGL
    GLESv2
    OpenSLES
    dl
)

target_link_options(main PRIVATE
    "-Wl,-u,ANativeActivity_onCreate"
)
