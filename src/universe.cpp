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

void Universe::next()
{
  for (int r{}; r < this->rowCount; r++)
  {
    for (int c{}; c < this->colCount; c++)
    {
      Region *pRegion = this->grid[r][c];

      // Evolve each regions
      *pRegion = pRegion->evolve();
    }
  }
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

void expand()
{
}