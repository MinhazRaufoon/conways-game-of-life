#include "game_of_life.h"
#include "universe.h"
#include "region.h"

Universe *g_conwayUniverse{nullptr};

int GameOfLife_Init(
    std::function<void(int, int)> pointDrawer,
    std::function<void()> displayCleaner,
    std::function<void()> displayUpdater)
{
  std::cout << "Initializing game..." << std::endl;

  g_conwayUniverse = new Universe;

  g_conwayUniverse->setDisplayCleaner(displayCleaner);
  g_conwayUniverse->setDisplayUpdater(displayUpdater);
  g_conwayUniverse->setPointDrawer(pointDrawer);

  std::cout << "Initialize successful!" << std::endl;

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
  std::cout << "Begining game..." << std::endl;
  g_conwayUniverse->begin();
  std::cout << "Game has begun" << std::endl;
  return 0;
}

int GameOfLife_Exit()
{
  std::cout << "Exiting game..." << std::endl;
  g_conwayUniverse->end();

  if (g_conwayUniverse != nullptr)
    delete g_conwayUniverse;

  std::cout << "Successfully exited" << std::endl;
  return 0;
}