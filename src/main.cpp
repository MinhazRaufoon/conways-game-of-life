#include <thread>
#include <chrono>
#include "universe.h"
#include <SFML/Graphics.hpp>

void conwaySimulationThread(Universe *conwayUniverse)
{
  conwayUniverse->begin();

  while (conwayUniverse->isRunning())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    conwayUniverse->display();
    conwayUniverse->next();
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(Universe::HEIGHT, Universe::WIDTH), "Conway's Game of Life");

  Universe conwayUniverse;

  /* Set view related functions */
  conwayUniverse.setPointDrawer(
      [&window](int x, int y)
      {
        sf::RectangleShape rectangle(sf::Vector2f(Universe::POINTSCALE, Universe::POINTSCALE));
        rectangle.setPosition(x + Universe::POINTSCALE * (x - 1), y + Universe::POINTSCALE * (y - 1));
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);
      });

  conwayUniverse.setDisplayCleaner(
      [&window]()
      {
        window.clear();
      });

  conwayUniverse.setDisplayUpdater(
      [&window]()
      {
        window.display();
      });

  /* Create necessary threads */
  std::thread conwayThread(conwaySimulationThread, &conwayUniverse);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        conwayUniverse.end();
        window.close();
      }
    }
  }

  /* Join for threads */
  conwayThread.join();

  return 0;
}