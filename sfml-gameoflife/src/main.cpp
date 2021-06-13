#include "../includes/game_of_life.h"
#include <SFML/Graphics.hpp>

int main()
{
  constexpr int SCALE{3};
  const int WWIDTH{GameOfLife_GetTotalHorizontalCells() * SCALE};
  const int WHEIGHT{GameOfLife_GetTotalVerticalCells() * SCALE};

  sf::RenderWindow window(sf::VideoMode(WHEIGHT, WWIDTH), "Conway's Game of Life");

  auto pointDrawer = [&window](int x, int y)
  {
    sf::RectangleShape rectangle(sf::Vector2f(SCALE, SCALE));
    rectangle.setPosition(x + SCALE * (x - 1), y + SCALE * (y - 1));
    rectangle.setFillColor(sf::Color::Green);
    window.draw(rectangle);
  };

  auto displayCleaner = [&window]()
  {
    window.clear();
  };

  auto displayUpdater = [&window]()
  {
    window.display();
  };

  GameOfLife_Init(pointDrawer, displayCleaner, displayUpdater);

  GameOfLife_Begin();

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        GameOfLife_Exit();
        window.close();
      }
    }
  }

  return 0;
}