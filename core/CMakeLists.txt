cmake_minimum_required(VERSION 3.22.1)

# Configuración independiente de AldratharCore
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(AldratharCore LANGUAGES CXX)

    include(CTest)
endif()

# Biblioteca principal
add_library(AldratharCore STATIC
    src/objects/GameObject.cpp
)

target_include_directories(AldratharCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AldratharCore
    PUBLIC
        cxx_std_20
)

set_target_properties(AldratharCore PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_options(AldratharCore PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Pruebas unitarias
if(BUILD_TESTING)
    add_executable(GameObjectTests
        tests/GameObjectTests.cpp
    )

    target_link_libraries(GameObjectTests
        PRIVATE
            AldratharCore
    )

    target_compile_options(GameObjectTests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    add_test(
        NAME GameObjectTests
        COMMAND GameObjectTests
    )
endif()
