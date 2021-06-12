#include "universe.h"

void Universe::begin()
{
  Region *pReg = new Region;
  this->regions.push_back(pReg);

  Region &reg = *pReg;
  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(11, 11) = true;
  reg(9, 11) = true;
  reg(9, 12) = true;
}

void Universe::next()
{
  for (Region *pReg : this->regions)
  {
    *pReg = pReg->evolve();
  }
}

Universe::~Universe()
{
  for (Region *pReg : this->regions)
  {
    delete pReg;
  }
}