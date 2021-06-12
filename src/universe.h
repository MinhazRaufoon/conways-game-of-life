#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "region.h"

class Universe
{
public:
  static constexpr int MAX_ROWS{10};
  static constexpr int MAX_COLS{10};

  std::vector<Region *> regions;

  void begin();

  ~Universe();
};

#endif