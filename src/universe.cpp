#include "universe.h"

void Universe::begin()
{
  this->regions.push_back(new Region);

  Region &reg = *this->regions[0];

  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(11, 11) = true;
  reg(9, 11) = true;
  reg(9, 12) = true;

  std::cout << reg << std::endl;

  std::cout << std::endl;

  //reg = reg.evolve();

  //std::cout << reg << std::endl;
}

Universe::~Universe()
{
  for (auto pReg : this->regions)
  {
    delete pReg;
  }
}