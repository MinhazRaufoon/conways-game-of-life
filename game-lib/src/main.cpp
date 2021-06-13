#include "universe.h"
#include "game_of_life.h"
#include <SFML/Graphics.hpp>

int main()
{
  constexpr int SCALE{3};
  const int WWIDTH{GameOfLife_GetTotalHorizontalCells() * SCALE};
  const int WHEIGHT{GameOfLife_GetTotalVerticalCells() * SCALE};

  sf::RenderWindow window(sf::VideoMode(WHEIGHT, WWIDTH), "Conway's Game of Life");

  Universe conwayUniverse;

  /* Set view related functions */
  conwayUniverse.setPointDrawer(
      [&window](int x, int y)
      {
        sf::RectangleShape rectangle(sf::Vector2f(SCALE, SCALE));
        rectangle.setPosition(x + SCALE * (x - 1), y + SCALE * (y - 1));
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

  conwayUniverse.begin();

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

  return 0;
}