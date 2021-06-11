#include "region.h"

int main()
{
  Region reg;
  reg(10, 10) = true;
  reg(10, 11) = true;
  reg(10, 12) = true;
  std::cout << reg << std::endl;
  return 0;
}