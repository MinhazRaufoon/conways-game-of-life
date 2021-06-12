#include "universe.h"

Universe::Universe()
    : rowCount{1}, colCount{1}
{
  // Create an initial region and add it to universe
  Region *pReg = new Region;
  this->regions[0][0] = pReg;

  // Make some cells alive as an initial state
  Region &reg = *pReg;
  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(11, 11) = true;
  reg(9, 11) = true;
  reg(9, 12) = true;
}

void Universe::begin()
{
}

void Universe::evolveAllRegions()
{
  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      Region *pRegion = this->regions[r][c];

      // Copy the neighbor edges
      if (r > 0)
        pRegion->setTopNeighborEdge(*this->regions[r - 1][c]);

      if (c < this->colCount - 1)
        pRegion->setRightNeighborEdge(*this->regions[r][c + 1]);

      if (r < this->rowCount - 1)
        pRegion->setBottomNeighborEdge(*this->regions[r + 1][c]);

      if (c > 0)
        pRegion->setLeftNeighborEdge(*this->regions[r][c - 1]);

      // Evolve each regions
      *pRegion = pRegion->evolve();
    }
  }
}

bool Universe::shouldExpandUp()
{
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
  this->rowCount++;
}

void Universe::expandDown()
{
  this->rowCount++;
}

void Universe::expandLeft()
{
  this->colCount++;
}

void Universe::expandRight()
{
  this->colCount++;

  int lastCol{this->colCount - 1};

  // Create the last column with new regions
  for (int r{}; r < this->rowCount; r++)
  {
    this->regions[r][lastCol] = new Region(r, lastCol);
  }
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
  this->evolveAllRegions();
  this->expand();
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
}
