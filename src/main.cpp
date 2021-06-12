#include <thread>
#include "universe.h"
#include "concurrent.h"
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(Universe::HEIGHT, Universe::WIDTH), "Conway's Game of Life");

  Universe conwayUniverse;

  /* Set view related functions */
  conwayUniverse.setPointDrawer(
      [&window](int x, int y)
      {
        sf::Vertex point(sf::Vector2f(x, y), sf::Color::Green);
        window.draw(&point, 1, sf::Points);
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