#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "ShipSelector.h"
#include <vector>

class GameBoard
{
public:
    struct Cell
    {
        sf::RectangleShape shape;
        bool onFocus = false;
        bool occupied = false;
    };

    void Init();
    void Draw(sf::RenderWindow& window);
    void OnInputEvent(const sf::Event& event, const sf::RenderWindow& window);

    std::vector<std::vector<Cell>> m_cells;
    std::vector<Cell*> m_focusedCells;

private:
    ShipSelector m_shipSelector;
};
