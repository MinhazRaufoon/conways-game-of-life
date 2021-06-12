#include <thread>
#include <chrono>
#include "universe.h"

void conwaySimulationThread(Universe *conwayUniverse)
{
  conwayUniverse->begin();

  while (conwayUniverse->isRunning())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    conwayUniverse->next();
    conwayUniverse->display();
  }
}