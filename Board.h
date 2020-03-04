#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>


namespace board
{
    static constexpr u_int8_t bord_size = 10;

class Board
{
private:
    sf::Font m_font;
public:
    void Init(sf::Vector2f initialPos);
    void Draw(sf::RenderWindow& window);
    std::vector<int> GetContactPos(const sf::Sprite& sprite, int maxContactCount);

    std::vector<sf::RectangleShape> m_shapes;
};

}
