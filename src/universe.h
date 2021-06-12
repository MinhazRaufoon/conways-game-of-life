#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <array>
#include "region.h"

class Universe
{
public:
  static constexpr int MAX_ROWS{50};
  static constexpr int MAX_COLS{30};
  static constexpr int WIDTH{MAX_COLS * Region::LENGTH};
  static constexpr int HEIGHT{MAX_ROWS * Region::LENGTH};

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

  void display();

  friend std::ostream &operator<<(std::ostream &out, const Universe &universe);

  ~Universe();
};

#endif