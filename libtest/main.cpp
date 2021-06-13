#include "includes/game_of_life.h"

int main()
{
  GameOfLife_Init([](int, int) {}, []() {}, []() {});
  GameOfLife_Begin();
  GameOfLife_Exit();
  return 0;
}