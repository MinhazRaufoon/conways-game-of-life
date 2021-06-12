#include <thread>
#include <chrono>
#include "universe.h"

void conwaySimulationThread(Universe *conwayUniverse)
{
  int c{10};
  while (conwayUniverse->isRunning() && c--)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    conwayUniverse->next();
  }
}