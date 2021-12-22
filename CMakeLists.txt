cmake_minimum_required(VERSION 3.20)
project(Rubiks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CubeSolver_VERSION_MAJOR 0)
set(CubeSolver_VERSION_MINOR 1)

configure_file(include/config.h.in
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h"
        )

add_executable(CubeSolver "")

target_include_directories(CubeSolver
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

set_target_properties(CubeSolver
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>"
        )

target_sources(CubeSolver
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cube.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/patterns.cpp
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cube.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/patterns.h
        )


target_precompile_headers(CubeSolver
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h
        )
