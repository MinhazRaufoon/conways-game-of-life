#include "universe.h"

void Universe::begin()
{
  // Create an initial region and add it to universe
  Region *pReg = new Region;
  this->regions.push_back(pReg);

  // Make some cells alive as an initial state
  Region &reg = *pReg;
  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(11, 11) = true;
  reg(9, 11) = true;
  reg(9, 12) = true;
}

void Universe::next()
{
  // Evolve every region
  for (Region *pRegion : this->regions)
  {
    *pRegion = pRegion->evolve();
  }
}

Universe::~Universe()
{
  // Clear regions in the dynamic memory
  for (Region *pRegion : this->regions)
  {
    delete pRegion;
  }
}

void expand()
{
}