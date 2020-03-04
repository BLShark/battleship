#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "GameBoard/GameBoard.h"

#include <functional>
#include <iostream>
#include <memory>

int main()
{
    sf::RenderWindow window({800, 600}, "SFML window");
    window.setFramerateLimit(60);

    GameBoard m_gameBoard;
    m_gameBoard.Init();

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            m_gameBoard.OnInputEvent(event, window);
        }
        m_gameBoard.Draw(window);

        window.display();
    }
    return 0;
}
