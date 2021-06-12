cmake_minimum_required(VERSION 3.17)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_STATIC_LIBRARIES TRUE)

find_package (Threads)

add_executable(GameOfLife src/main.cpp src/region.h src/region.cpp src/universe.h src/universe.cpp)

target_link_libraries(GameOfLife sfml-graphics sfml-window sfml-system)
target_link_libraries (GameOfLife ${CMAKE_THREAD_LIBS_INIT})
