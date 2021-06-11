#include "region.h"

std::ostream &operator<<(std::ostream &out, const Region &region)
{
  for (auto &line : region.grid)
  {
    for (const bool &cell : line)
    {
      out << cell;
    }
    out << std::endl;
  }
  return out;
}