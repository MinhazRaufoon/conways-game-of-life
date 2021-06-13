#include "game_of_life.h"
#include "universe.h"
#include "region.h"

Universe *g_conwayUniverse{nullptr};

int GameOfLife_Init(
    std::function<void(int, int)> pointDrawer,
    std::function<void()> displayCleaner,
    std::function<void()> displayUpdater)
{
  g_conwayUniverse = new Universe;

  g_conwayUniverse->setDisplayCleaner(displayCleaner);
  g_conwayUniverse->setDisplayUpdater(displayUpdater);
  g_conwayUniverse->setPointDrawer(pointDrawer);

  return 0;
}

int GameOfLife_GetTotalHorizontalCells()
{
  return Universe::MAX_COLS * Region::LENGTH;
}

int GameOfLife_GetTotalVerticalCells()
{
  return Universe::MAX_ROWS * Region::LENGTH;
}

int GameOfLife_Begin()
{
  g_conwayUniverse->begin();
  return 0;
}

int GameOfLife_Exit()
{
  g_conwayUniverse->end();
  delete g_conwayUniverse;
  return 0;
}