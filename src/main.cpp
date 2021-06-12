#include <thread>
#include "universe.h"
#include "concurrent.h"
#include <SFML/Graphics.hpp>

int main()
{
  Universe conwayUniverse;
  sf::RenderWindow window(sf::VideoMode(Universe::HEIGHT, Universe::WIDTH), "Conway's Game of Life");

  std::thread conwayThread(conwaySimulationThread, &conwayUniverse);

  //sf::Vertex point(sf::Vector2f(1, 1), sf::Color::Green);

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

    // window.clear();
    // window.draw(&point, 1, sf::Points);
    // window.display();
  }

  conwayThread.join();

  return 0;
}