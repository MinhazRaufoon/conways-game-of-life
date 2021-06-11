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
    return this->neighborEdges["top"][col];
  else if (row >= this->LENGTH)
    return this->neighborEdges["bottom"][col];
  else if (col < 0)
    return this->neighborEdges["left"][row];
  else if (col >= this->LENGTH)
    return this->neighborEdges["right"][row];
  else
    return this->grid[row][col];
}

bool &Region::cell(int row, int col)
{
  return this->operator()(row, col);
}

int Region::countAliveNeighbors(int row, int col)
{
  int count{0};
  for (int i{row - 1}; i <= row + 1; i++)
  {
    for (int j{col - 1}; j <= col + 1; j++)
    {
      if (i == row && j == col)
        continue;
      if (cell(i, j))
        count++;
    }
  }
  return count;
}

int Region::countDeadNeighbors(int row, int col)
{
  return 8 - this->countAliveNeighbors(row, col);
}

Region Region::evolve()
{
  Region evolved;

  // For all cells
  for (int r{}; r < this->LENGTH; r++)
  {
    for (int c{}; c < this->LENGTH; c++)
    {
      int aliveNeighborCount = this->countAliveNeighbors(r, c);

      if (this->cell(r, c))
      {
        // For alive cell
        evolved.cell(r, c) = aliveNeighborCount == 2 || aliveNeighborCount == 3;
      }
      else
      {
        // For dead cell
        evolved.cell(r, c) = aliveNeighborCount == 3;
      }
    }
  }

  return evolved;
}