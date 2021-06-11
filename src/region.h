#ifndef REGION_H
#define REGION_H

#include <array>
#include <bitset>
#include <iostream>

class Region
{
public:
  /* Region dimensions */
  static constexpr int WIDTH{20};
  static constexpr int HEIGHT{20};

  /* The area of the region consisting of WIDTH x HEIGHT bits */
  std::array<std::bitset<WIDTH>, HEIGHT> grid;

  /* To output the region */
  friend std::ostream &operator<<(std::ostream &out, const Region &region);
};

#endif