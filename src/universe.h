#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "region.h"

class Universe
{
private:
  std::vector<Region *> regions;

  void expand();

public:
  static constexpr int MAX_ROWS{10};
  static constexpr int MAX_COLS{10};

  void begin();

  void next();

  ~Universe();
};

#endif