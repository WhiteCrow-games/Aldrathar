cmake_minimum_required(VERSION 3.16)

project(Aldrathar VERSION 0.0.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(Aldratharv0.0.4 ${SOURCES})
