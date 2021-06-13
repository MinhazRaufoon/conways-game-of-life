cmake_minimum_required(VERSION 3.9)

project(SFMLGameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

find_package (Threads)

set(SFML_STATIC_LIBRARIES TRUE)

link_directories(libs/)
link_libraries(-l:game_of_life.a)

add_executable(SFMLGameOfLife src/main.cpp includes/game_of_life.h)

target_link_libraries(SFMLGameOfLife sfml-graphics sfml-window sfml-system)
target_link_libraries (SFMLGameOfLife ${CMAKE_THREAD_LIBS_INIT})
