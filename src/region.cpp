#include <iostream>
#include "region.h"

std::ostream &operator<<(std::ostream &out, const Region &region)
{
  for (auto &line : region.grid)
  {
    out << line << std::endl;
  }
  return out;
}