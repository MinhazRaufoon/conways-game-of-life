#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <functional>

int GameOfLife_Init(
    std::function<void(int, int)> pointDrawer,
    std::function<void()> displayCleaner,
    std::function<void()> displayUpdater);

int GameOfLife_GetTotalHorizontalCells();

int GameOfLife_GetTotalVerticalCells();

int GameOfLife_Begin();

int GameOfLife_Exit();

#endif