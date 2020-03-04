#include "Board.h"
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <iostream>
namespace board {

void Board::Init(sf::Vector2f initialPos)
{
    const int m_size = 50;
    const int m_thickness = 2;
    sf::Vector2f pos = initialPos + sf::Vector2f(m_thickness, m_thickness);
    m_shapes.resize(bord_size * bord_size);
    for(int y = 0; y < bord_size; y++)
    {
        for(int x = 0; x < bord_size; x++)
        {
            sf::RectangleShape& shape = m_shapes[(y * bord_size) + x];
            shape.setFillColor(sf::Color(49, 187, 191));
            shape.setSize(sf::Vector2f(m_size, m_size));
            shape.setPosition(pos);
            shape.setOutlineColor(sf::Color::White);
            shape.setOutlineThickness(m_thickness);
            pos.x += m_size + m_thickness;
        }
        pos.x = initialPos.x + m_thickness;
        pos.y += m_size + m_thickness;
    }


    if (!m_font.loadFromFile("../Assets/Arial.ttf"))
    {
        std::cout<<"cannot load font \n"<<std::endl;
    }
}

void Board::Draw(sf::RenderWindow& window)
{
    sf::Text txt;
    txt.setFont(m_font);
    txt.setColor(sf::Color::Black);

    for(size_t index = 0; index < m_shapes.size(); index++)
    {
        window.draw(m_shapes.at(index));
        txt.setString(std::to_string(index));

        txt.setOrigin(txt.getGlobalBounds().width/2 , txt.getGlobalBounds().height /2 );
        auto rect = m_shapes[index].getGlobalBounds();
        txt.setPosition(rect.left + rect.width /2  , rect.top + rect.height/2);
        window.draw(txt);

    }
}

std::vector<int> Board::GetContactPos(const sf::Sprite& sprite, int maxContactCount)
{
    std::vector<int> contactPos;
    std::vector<int> result;
    for(size_t i = 0; i < m_shapes.size(); i++)
    {
        if(m_shapes[i].getGlobalBounds().intersects(sprite.getGlobalBounds()))
        {
            contactPos.push_back(i);
        }
    }

    auto path_lenght = [](int x1, int y1, int x2, int y2)->float
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    };

    if(sprite.getRotation() == 0.0f || sprite.getRotation() == 180)
    {
        if(contactPos.size() > maxContactCount)
        {
            auto p1 = sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2), sprite.getPosition().y);
            auto p2 = sf::Vector2f(m_shapes[contactPos[0]].getPosition().x + m_shapes[contactPos[0]].getGlobalBounds().width / 2, m_shapes[contactPos[0]].getPosition().y);
            auto p3 = sf::Vector2f(m_shapes[contactPos[1]].getPosition().x + m_shapes[contactPos[1]].getGlobalBounds().width / 2, m_shapes[contactPos[1]].getPosition().y);

            auto test1 = path_lenght(m_shapes[contactPos[0]].getPosition().x + m_shapes[contactPos[0]].getGlobalBounds().width / 2 ,
                                     m_shapes[contactPos[0]].getPosition().y + m_shapes[contactPos[0]].getGlobalBounds().height / 2 , p1.x, p1.y);
            auto test2 = path_lenght(m_shapes[contactPos[1]].getPosition().x + m_shapes[contactPos[1]].getGlobalBounds().width / 2 ,
                                     m_shapes[contactPos[1]].getPosition().y + m_shapes[contactPos[1]].getGlobalBounds().height / 2 , p1.x, p1.y);
            auto dest1 = std::abs(p1.x - p2.x);
            auto dest2 = std::abs(p3.x - p1.x);

            bool even = dest1 < dest2;
            for(size_t i = 0; i < contactPos.size(); i++)
            {
                if(even)
                {
                    if(i % 2 == 0)
                    {
                        result.emplace_back(contactPos[i]);
                    }
                }
                else
                {
                    if(i % 2 != 0)
                    {
                        result.emplace_back(contactPos[i]);
                    }
                }
            }
        }
        else
        {
            result = contactPos;
        }
    }


    return result;
}

}
