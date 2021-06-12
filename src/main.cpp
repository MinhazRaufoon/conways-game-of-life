#include "universe.h"

int main()
{
  Universe conwayUniverse;

  conwayUniverse.begin();

  std::cout << "---------------" << std::endl;

  conwayUniverse.next();

  std::cout << "---------------" << std::endl;

  conwayUniverse.next();
  return 0;
}