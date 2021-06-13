#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include "universe.h"

int g_regionCount = 1;

Universe::Universe()
    : rowCount{1}, colCount{1}
{
  // Create an initial region and add it to universe
  Region *pReg = new Region;
  this->regions[0][0] = pReg;

  // Make some cells alive as an initial state

  int i{Region::LENGTH / 2};

  Region &reg = *pReg;

  reg(i, i) = true;
  reg(i, i + 1) = true;
  reg(i + 1, i + 1) = true;
  reg(i - 1, i + 1) = true;
  reg(i - 1, i + 2) = true;
}

void Universe::setPointDrawer(std::function<void(int, int)> func)
{
  this->pointDrawer = func;
}

void Universe::setDisplayCleaner(std::function<void()> func)
{
  this->displayCleaner = func;
}

void Universe::setDisplayUpdater(std::function<void()> func)
{
  this->displayUpdater = func;
}

void conwaySimulationThread(Universe *conwayUniverse)
{
  while (conwayUniverse->isRunning())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    conwayUniverse->display();
    conwayUniverse->next();
  }
}

void Universe::begin()
{
  this->running = true;
  this->conwayThread = new std::thread(conwaySimulationThread, this);
}

void Universe::end()
{
  if (!this->running)
    return;

  this->running = false;
  this->conwayThread->join();
}

bool Universe::isRunning()
{
  return this->running;
}

void Universe::assignNeighborEdgesParallely()
{
  std::vector<std::thread> workerThreads;
  std::vector<std::function<void()>> neighborEdgeCalcTasks;

  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      neighborEdgeCalcTasks.push_back(
          [r, c, this]() mutable
          {
            Region *pRegion = this->regions[r][c];
            auto &regions = this->regions;

            /* Copy neighbor edges */
            if (r > 0)
              pRegion->setTopNeighborEdge(*regions[r - 1][c]);

            if (c < colCount - 1)
              pRegion->setRightNeighborEdge(*regions[r][c + 1]);

            if (r < rowCount - 1)
              pRegion->setBottomNeighborEdge(*regions[r + 1][c]);

            if (c > 0)
              pRegion->setLeftNeighborEdge(*regions[r][c - 1]);
          });
    }
  }

  /* Run neighbor edge allocation tasks parallely and synchronize */
  for (auto task : neighborEdgeCalcTasks)
    workerThreads.push_back(std::thread(task));

  for (std::thread &thread : workerThreads)
    thread.join();
}

void Universe::evolveAllRegionsParallely()
{
  std::vector<std::thread> workerThreads;
  std::vector<std::function<void()>> evolutionTasks;

  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      evolutionTasks.push_back(
          [r, c, this]() mutable
          {
            Region *pRegion = this->regions[r][c];
            /* Set corner points */
            /*
            if (r > 0 && c > 0)
              pRegion->setTopLeftNeighborCorner(regions[r - 1][c - 1]);

            if (r > 0 && c < Universe::MAX_COLS - 1)
              pRegion->setTopRightNeighborCorner(regions[r - 1][c + 1]);

            if (r < Universe::MAX_ROWS - 1 && c > 0)
              pRegion->setBottomLeftNeighborCorner(regions[r + 1][c - 1]);

            if (r < Universe::MAX_ROWS - 1 && c < Universe::MAX_COLS - 1)
              pRegion->setBottomRightNeighborCorner(regions[r + 1][c + 1]);
            */

            // Evolve each regions
            pRegion->evolve();
          });
    }
  }

  /* Evolve each regions parallelly and sync */
  for (auto task : evolutionTasks)
    workerThreads.push_back(std::thread(task));

  for (std::thread &thread : workerThreads)
    thread.join();
}

bool Universe::shouldExpandUp()
{
  if (this->rowCount == this->MAX_ROWS)
    return false;

  for (int c{}; c < this->colCount; c++)
  {
    // If any region at top edge is reproductive
    if (this->regions[0][c]->hasReproductiveTop())
      return true;
  }
  return false;
}

bool Universe::shouldExpandDown()
{
  if (this->rowCount == this->MAX_ROWS)
    return false;

  for (int c{}; c < this->colCount; c++)
  {
    // If any region at bottom edge is reproductive
    if (this->regions[this->rowCount - 1][c]->hasReproductiveBottom())
      return true;
  }
  return false;
}

bool Universe::shouldExpandLeft()
{
  if (this->colCount == this->MAX_COLS)
    return false;

  for (int r{}; r < this->rowCount; r++)
  {
    // If any region at left edge is reproductive
    if (this->regions[r][0]->hasReproductiveLeft())
      return true;
  }
  return false;
}

bool Universe::shouldExpandRight()
{
  if (this->colCount == this->MAX_COLS)
    return false;

  for (int r{}; r < this->rowCount; r++)
  {
    // If any region at right edge is reproductive
    if (this->regions[r][this->colCount - 1]->hasReproductiveRight())
      return true;
  }
  return false;
}

void Universe::expandUp()
{
  for (int r{this->rowCount - 1}; r >= 0; r--)
  {
    for (int c{0}; c < this->colCount; c++)
    {
      // Shift every region by 1 downward to make room at the top
      this->regions[r + 1][c] = this->regions[r][c];
    }
  }

  this->rowCount++;

  // Create the first row with new regions
  for (int c{}; c < this->colCount; c++)
  {
    this->regions[0][c] = new Region;
    g_regionCount++;
  }

  std::cout << "Universe expanded upward######################" << std::endl;
}

void Universe::expandDown()
{
  this->rowCount++;

  int lastRow{this->rowCount - 1};

  // Create the last row with new regions
  for (int c{}; c < this->colCount; c++)
  {
    this->regions[lastRow][c] = new Region;
    g_regionCount++;
  }

  std::cout << "Universe expanded downward######################" << std::endl;
}

void Universe::expandLeft()
{
  for (int r{0}; r < this->rowCount; r++)
  {
    for (int c{this->colCount - 1}; c >= 0; c--)
    {
      // Shift every region by 1 toward right to make room at left
      this->regions[r][c + 1] = this->regions[r][c];
    }
  }

  this->colCount++;

  // Create the first column with new regions
  for (int r{}; r < this->rowCount; r++)
  {
    this->regions[r][0] = new Region;
    g_regionCount++;
  }
  std::cout << "Universe expanded left######################" << std::endl;
}

void Universe::expandRight()
{
  this->colCount++;

  int lastCol{this->colCount - 1};

  // Create the last column with new regions
  for (int r{}; r < this->rowCount; r++)
  {
    this->regions[r][lastCol] = new Region;
    g_regionCount++;
  }
  std::cout << "Universe expanded right######################" << std::endl;
}

void Universe::expand()
{
  if (this->shouldExpandRight())
    this->expandRight();

  if (this->shouldExpandDown())
    this->expandDown();

  if (this->shouldExpandUp())
    this->expandUp();

  if (this->shouldExpandLeft())
    this->expandLeft();
}

void Universe::next()
{
  std::cout << "Universe : " << this->rowCount << " x " << this->colCount << std::endl;
  std::cout << "Total regions created: " << g_regionCount << std::endl;
  std::cout << "###########Evolution begins##########" << std::endl;

  this->assignNeighborEdgesParallely();
  this->evolveAllRegionsParallely();
  this->expand();
}

void Universe::display()
{
  if (!this->pointDrawer || !this->displayUpdater || !this->displayCleaner)
    return;

  this->displayCleaner();

  // Render all regions
  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      this->renderRegion(r, c);
    }
  }

  this->displayUpdater();
}

void Universe::renderRegion(int row, int col)
{
  Region &region = *this->regions[row][col];

  for (int r{}; r < Region::LENGTH; r++)
  {
    for (int c{}; c < Region::LENGTH; c++)
    {
      if (region(r, c))
      {
        int x{row * Region::LENGTH + r + 1};
        int y{col * Region::LENGTH + c + 1};
        this->pointDrawer(x, y);
      }
    }
  }
}

std::ostream &operator<<(std::ostream &out, const Universe &universe)
{
  char alive{'O'};
  char dead{'.'};

  for (int r{}; r < universe.rowCount; r++)
  {
    for (int c{}; c < universe.colCount; c++)
    {
      out << "Region at (" << r << ", " << c << ")" << std::endl;
      out << *universe.regions[r][c] << std::endl
          << std::endl;
    }
  }

  return out;
}

Universe::~Universe()
{
  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      // Free memory of each region
      delete this->regions[r][c];
    }
  }

  delete this->conwayThread;
}
