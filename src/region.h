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
  static constexpr int LENGTH{20};

  /* The area of the region consisting of WIDTH x HEIGHT bits */
  std::array<std::array<bool, LENGTH>, LENGTH> grid{};

  /* Neighbor edges */
  std::map<std::string, std::array<bool, LENGTH>> neighborEdges{
      {"top", {}},
      {"right", {}},
      {"bottom", {}},
      {"left", {}},
  };

  /* Operators */
  bool &operator()(int row, int col);

  /* To output the region */
  friend std::ostream &operator<<(std::ostream &out, const Region &region);
};

#endif