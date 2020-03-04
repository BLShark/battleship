#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

enum ShipStatus
{
    IDLE,
    RESERVED
};

class Ship
{
public:
    void Init(const std::string& resourceId, size_t sz);
    void Draw(sf::RenderWindow& window);

    ShipStatus status = ShipStatus::IDLE;
    sf::Sprite sprite;
    size_t size;
};
