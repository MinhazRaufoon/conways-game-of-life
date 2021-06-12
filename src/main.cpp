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

  int x{100};

  Region &ref = reg;

  while (x--)
  {
    std::cout << std::endl;
    ref = ref.evolve();
    std::cout << ref << std::endl;
  }

  return 0;
}