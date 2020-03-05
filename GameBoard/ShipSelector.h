#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Ship.h"

class ShipSelector
{
public:
    void Init();
    void Draw(sf::RenderWindow& window);
    void OnInputEvent(const sf::Event &event, const sf::RenderWindow& window);
    void DeactivateShip();

    Ship* GetSelectedShip();
private:
    std::vector<Ship> m_allShips;
    Ship* m_selectedShip = nullptr;
    float m_rotation = 0;
};
