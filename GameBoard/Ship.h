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
    std::vector<sf::Vector2i> GetPositions();

    void Rotate();
    int GetRotation() const;

    int GetSize() const;
    sf::Sprite& GetSprite();

    ShipStatus status = ShipStatus::IDLE;
private:
    sf::Sprite m_sprite;
    size_t m_size = 0;
    int m_rotation = 0;
    std::vector<sf::Vector2i> m_positions;
};
