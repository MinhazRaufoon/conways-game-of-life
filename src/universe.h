#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <array>
#include <functional>
#include "region.h"

class Universe
{
public:
  static constexpr int MAX_ROWS{12};
  static constexpr int MAX_COLS{7};

  static constexpr int POINTSCALE{3};
  static constexpr int WIDTH{POINTSCALE * MAX_COLS * Region::LENGTH};
  static constexpr int HEIGHT{POINTSCALE * MAX_ROWS * Region::LENGTH};

private:
  std::array<std::array<Region *, MAX_COLS>, MAX_ROWS> regions{};

  bool running{false};

  /* Dynamically assigned view related functions */
  std::function<void(int, int)> pointDrawer{};
  std::function<void()> displayCleaner{};
  std::function<void()> displayUpdater{};

  bool shouldExpandUp();
  bool shouldExpandDown();
  bool shouldExpandLeft();
  bool shouldExpandRight();

  void expandUp();
  void expandDown();
  void expandLeft();
  void expandRight();

  void expand();

  void evolveAllRegions();

  void renderRegion(int row, int col);

public:
  int rowCount;
  int colCount;

  Universe();

  void setPointDrawer(std::function<void(int, int)>);

  void setDisplayCleaner(std::function<void()>);

  void setDisplayUpdater(std::function<void()>);

  bool isRunning();

  void begin();

  void end();

  void next();

  void display();

  friend std::ostream &operator<<(std::ostream &out, const Universe &universe);

  ~Universe();
};

#endif