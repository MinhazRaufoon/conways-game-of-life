#ifndef REGION_H
#define REGION_H

#include <array>
#include <bitset>
#include <iostream>

class Region
{
public:
  /* Region dimension of each side */
  static constexpr int LENGTH{20};

  /* The area of the region consisting of WIDTH x HEIGHT bits */
  std::array<std::array<bool, LENGTH>, LENGTH> grid;

  /* Constructors */
  Region() : grid{} {}

  /* Operators */
  auto &operator[](int index) { return this->grid[index]; }

  /* To output the region */
  friend std::ostream &operator<<(std::ostream &out, const Region &region);
};

#endif