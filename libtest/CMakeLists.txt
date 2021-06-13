cmake_minimum_required(VERSION 3.9)

project(GameOfLifeTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

find_package (Threads)

link_directories(libs/)
link_libraries(-l:game_of_life.a)

add_executable(GameOfLifeTest main.cpp includes/game_of_life.h)

target_link_libraries (GameOfLifeTest ${CMAKE_THREAD_LIBS_INIT})
