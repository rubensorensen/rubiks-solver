cmake_minimum_required(VERSION 3.20)
project(Rubiks)

set(CMAKE_CXX_STANDARD 20)

add_executable(CubeSolver "")

target_sources(CubeSolver
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Cube.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Patterns.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/Cube.h
        ${CMAKE_CURRENT_LIST_DIR}/include/Patterns.h
        )

target_include_directories(CubeSolver
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/include
        )