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

bool &Region ::operator()(int row, int col)
{
  if (row < 0)
  {
    return this->neighborEdges["top"][col];
  }
  else if (row >= this->LENGTH)
  {
    return this->neighborEdges["bottom"][col];
  }
  else if (col < 0)
  {
    return this->neighborEdges["left"][row];
  }
  else if (col >= this->LENGTH)
  {
    return this->neighborEdges["right"][row];
  }
  else
  {
    return this->grid[row][col];
  }
}