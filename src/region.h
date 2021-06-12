#ifndef REGION_H
#define REGION_H

#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <string>

class Region
{
public:
  /* Region dimension of each side */
  static constexpr int LENGTH{32};

private:
  /* Edges of top right bottom left neighbors */
  std::map<std::string, std::array<bool, LENGTH>> neighborEdges{
      {"top", {}},
      {"right", {}},
      {"bottom", {}},
      {"left", {}},
  };

  /* The grid of the region consists of WIDTH x HEIGHT bits */
  std::array<std::array<bool, LENGTH>, LENGTH> cells{};

  int countAliveNeighborCells(int row, int col);

  int countDeadNeighborCells(int row, int col);

public:
  /* Constructors */
  Region();

  // To get a cell at a position
  bool &cell(int row, int col);

  /* To calculate neighbors' edges */
  void setTopNeighborEdge(Region &topNeighbor);

  void setRightNeighborEdge(Region &rightNeighbor);

  void setBottomNeighborEdge(Region &bottomNeighbor);

  void setLeftNeighborEdge(Region &leftNeighbor);

  /* To evolve to next generation */
  Region evolve();

  /* To determine the reproductive edges */
  bool hasReproductiveTop();

  bool hasReproductiveBottom();

  bool hasReproductiveLeft();

  bool hasReproductiveRight();

  bool &operator()(int row, int col);

  friend std::ostream &operator<<(std::ostream &out, const Region &region);

  ~Region();
};

#endif