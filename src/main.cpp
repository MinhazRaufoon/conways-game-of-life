#include "region.h"

int main()
{
  Region reg;
  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(11, 11) = true;
  reg(9, 11) = true;
  reg(9, 12) = true;
  std::cout << reg << std::endl;

  std::cout << std::endl;

  std::cout << reg.evolve() << std::endl;

  return 0;
}