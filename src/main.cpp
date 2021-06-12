#include "universe.h"
#include <SFML/Graphics.hpp>

int main()
{
  Universe conwayUniverse;

  sf::RenderWindow window(sf::VideoMode(Universe::HEIGHT, Universe::WIDTH), "Conway's Game of Life");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  conwayUniverse.run();

  return 0;
}