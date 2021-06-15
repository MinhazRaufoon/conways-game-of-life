// sfml_gameoflife_windows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <Windows.h>

int main()
{
    constexpr int SCALE{ 3 };
    const int WWIDTH{ GameOfLife_GetTotalHorizontalCells() * SCALE };
    const int WHEIGHT{ GameOfLife_GetTotalVerticalCells() * SCALE };

    sf::RenderWindow window(sf::VideoMode(WHEIGHT, WWIDTH), "Conway's Game of Life");

    auto pointDrawer = [&window, SCALE](int x, int y)
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

    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

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
        GameOfLife_EvolveManually();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
