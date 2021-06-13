cmake_minimum_required(VERSION 3.9)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(SFML_STATIC_LIBRARIES TRUE)

find_package (Threads REQUIRED)

#add_executable(GameOfLife src/main.cpp src/game_of_life.h src/game_of_life.cpp src/region.h src/region.cpp src/universe.h src/universe.cpp)

add_library(game_of_life src/game_of_life.h src/game_of_life.cpp src/region.h src/region.cpp src/universe.h src/universe.cpp)

#target_link_libraries(GameOfLife sfml-graphics sfml-window sfml-system)
#target_link_libraries (GameOfLife ${CMAKE_THREAD_LIBS_INIT})

#target_link_libraries(game_of_life sfml-graphics sfml-window sfml-system)
target_link_libraries (game_of_life ${CMAKE_THREAD_LIBS_INIT})