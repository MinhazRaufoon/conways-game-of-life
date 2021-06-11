#include "region.h"

std::ostream &operator<<(std::ostream &out, const Region &region)
{
  char alive{'O'};
  char dead{'.'};

  for (auto &line : region.grid)
  {
    for (const bool &cell : line)
    {
      out << (cell ? alive : dead);
    }
    out << std::endl;
  }
  return out;
}