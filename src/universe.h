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
  std::array<std::array<Region *, MAX_COLS>, MAX_ROWS> regions{};

  bool shouldExpandUp();

  void expandUp();

  bool shouldExpandDown();

  void expandDown();

  bool shouldExpandLeft();

  void expandLeft();

  bool shouldExpandRight();

  void expandRight();

  void expand();

  void evolveAllRegions();

public:
  int rowCount;
  int colCount;

  Universe();

  void run();

  void next();

  ~Universe();
};

#endif