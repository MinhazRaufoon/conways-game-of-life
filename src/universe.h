#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <array>
#include "region.h"

class Universe
{
public:
  static constexpr int MAX_ROWS{10};
  static constexpr int MAX_COLS{10};

private:
  std::array<std::array<Region *, MAX_COLS>, MAX_ROWS> grid{};

  void expand();

  void evolveAllRegions();

public:
  int rowCount;
  int colCount;

  Universe();

  void begin();

  void next();

  ~Universe();
};

#endif