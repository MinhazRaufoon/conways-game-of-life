#include "universe.h"

Universe::Universe()
    : rowCount{1}, colCount{1}
{
  // Create an initial region and add it to universe
  Region *pReg = new Region;
  this->grid[0][0] = pReg;

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
      Region *pRegion = this->grid[r][c];

      // Copy the neighbor edges
      if (r > 0)
        pRegion->setTopNeighborEdge(*this->grid[r - 1][c]);

      if (c < this->colCount - 1)
        pRegion->setRightNeighborEdge(*this->grid[r][c + 1]);

      if (r < this->rowCount - 1)
        pRegion->setBottomNeighborEdge(*this->grid[r + 1][c]);

      if (c > 0)
        pRegion->setLeftNeighborEdge(*this->grid[r][c - 1]);

      // Evolve each regions
      *pRegion = pRegion->evolve();
    }
  }
}

void Universe::expand()
{
  bool shouldExpandUp{false};
  bool shouldExpandDown{false};
  bool shouldExpandLeft{false};
  bool shouldExpandRight{false};

  for (int c{}; c < this->colCount; c++)
  {
    if (this->grid[0][c]->hasReproductiveTop())
    {
      // If any region at top edge is reproductive
      shouldExpandUp = true;
      break;
    }
  }

  for (int c{}; c < this->colCount; c++)
  {
    if (this->grid[this->rowCount - 1][c]->hasReproductiveBottom())
    {
      // If any region at bottom edge is reproductive
      shouldExpandDown = true;
      break;
    }
  }

  for (int r{}; r < this->rowCount; r++)
  {
    if (this->grid[r][0]->hasReproductiveLeft())
    {
      // If any region at left edge is reproductive
      shouldExpandLeft = true;
      break;
    }
  }

  for (int r{}; r < this->rowCount; r++)
  {
    if (this->grid[r][this->colCount - 1]->hasReproductiveRight())
    {
      // If any region at right edge is reproductive
      shouldExpandRight = true;
      break;
    }
  }
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
      delete this->grid[r][c];
    }
  }
}
