#include "region.h"

Region::Region()
{
  std::cout << "Region created at " << this->rowIndex << "," << this->columnIndex << std::endl;
}

Region::~Region()
{
  std::cout << "Region destroyed at " << this->rowIndex << "," << this->columnIndex << std::endl;
}

Region::Region(int row, int col)
    : rowIndex{row}, columnIndex{col}
{
  std::cout << "Region created at " << this->rowIndex << "," << this->columnIndex << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Region &region)
{
  char alive{'O'};
  char dead{'.'};

  // Print each cell at appropriate positions in 2D region
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
  // If trying to access a cell from neighbor regions, read from this->neighborEdges
  if (row < 0)
    return this->neighborEdges["top"][col];
  else if (row >= this->LENGTH)
    return this->neighborEdges["bottom"][col];
  else if (col < 0)
    return this->neighborEdges["left"][row];
  else if (col >= this->LENGTH)
    return this->neighborEdges["right"][row];
  else
    // Otherwise, read normally from the current region's grid
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
      // Ignore self
      if (i == row && j == col)
        continue;

      // Count alive neighbor cells
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
        // Decide fate of the alive cell
        evolved.cell(r, c) = aliveNeighborCount == 2 || aliveNeighborCount == 3;
      }
      else
      {
        // Decide fate of the dead cell
        evolved.cell(r, c) = aliveNeighborCount == 3;
      }
    }
  }

  return evolved;
}

void Region::setTopNeighborEdge(Region &topNeighbor)
{
  std::string key{"top"};

  // Copy the bottom layer cells of top neighbor into this->neighborEdges["top"]
  for (int c{}; c < this->LENGTH; c++)
  {
    this->neighborEdges[key][c] = topNeighbor.cell(this->LENGTH - 1, c);
  }
}

void Region::setRightNeighborEdge(Region &rightNeighbor)
{
  std::string key{"right"};

  // Copy the left layer cells of right neighbor into this->neighborEdges["right"]
  for (int r{}; r < this->LENGTH; r++)
  {
    this->neighborEdges[key][r] = rightNeighbor.cell(r, 0);
  }
}

void Region::setBottomNeighborEdge(Region &bottomNeighbor)
{
  std::string key{"bottom"};

  // Copy the top layer cells of bottom neighbor into this->neighborEdges["bottom"]
  for (int c{}; c < this->LENGTH; c++)
  {
    this->neighborEdges[key][c] = bottomNeighbor.cell(0, c);
  }
}

void Region::setLeftNeighborEdge(Region &leftNeighbor)
{
  std::string key{"left"};

  // Copy the right layer cells of left neighbor into this->neighborEdges["left"]
  for (int r{}; r < this->LENGTH; r++)
  {
    this->neighborEdges[key][r] = leftNeighbor.cell(r, this->LENGTH - 1);
  }
}

void Region::adjustPosition(int newRow, int newCol)
{
  this->rowIndex = newRow;
  this->columnIndex = newCol;
}
