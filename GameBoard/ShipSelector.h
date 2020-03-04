#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Ship.h"

class ShipSelector
{
public:
    void Init(const std::vector<int>& shipSizes);
    void Draw(sf::RenderWindow& window);
    void OnInputEvent(const sf::Event &event, const sf::RenderWindow& window);
    bool IsShipSelected();
    uint8_t GetSelectedShipSize();
    void DeactivateShip();
private:
//    struct Ship
//    {
//        sf::RectangleShape shape;
//        sf::Text name;
//        ShipStatus status = ShipStatus::IDLE;
//        std::vector<sf::Vector2i> positions;
//    };
    std::vector<Ship> m_allShips;
    Ship* m_selectedShip = nullptr;
};
