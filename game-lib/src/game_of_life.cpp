#include "game_of_life.h"
#include "universe.h"
#include "region.h"

int GameOfLife_Init(
    std::function<void(int, int)> pointDrawer,
    std::function<void()> displayCleaner,
    std::function<void()> displayUpdater) { return 0; }

int GameOfLife_GetTotalHorizontalCells()
{
  return Universe::MAX_COLS * Region::LENGTH;
}

int GameOfLife_GetTotalVerticalCells()
{
  return Universe::MAX_ROWS * Region::LENGTH;
}

int GameOfLife_Begin() { return 0; }

int GameOfLife_Exit()
{
  return 0;
}