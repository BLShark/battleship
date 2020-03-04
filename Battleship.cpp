#include "Battleship.h"
#include <iostream>

void Battleship::Init(const std::string& image, board::Board* board, int boardSize)
{
    shipTexture.loadFromFile(image);
    shipSprite.setTexture(shipTexture);
    shipSprite.setOrigin(shipSprite.getTextureRect().width / 2, shipSprite.getTextureRect().height / 2);

    m_boardPtr = board;
    m_boardSize = boardSize;
}

void Battleship::Draw(sf::RenderWindow &window)
{
    window.draw(shipSprite);
}

void  Battleship::SetPossition(sf::Vector2f cord)
{
    shipSprite.setPosition(cord.x, cord.y);
}

void Battleship::OnEvent(const sf::Event& e, sf::RenderWindow *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) /*and !isPressed */)
    {
        auto translated_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if(!isPressed)
        {
            if(shipSprite.getGlobalBounds().contains(translated_pos))
            {
                isPressed = true;
            }
        }
        if(isPressed)
        {
            Move(translated_pos);
        }
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        auto translated_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (shipSprite.getGlobalBounds().contains(translated_pos))
        {
            Rotate();
        }
    }

    if (e.type == sf::Event::MouseButtonReleased)
    {
        isPressed = false;

        auto contactPos = m_boardPtr->GetContactPos(shipSprite, 5);
        for(auto& r : m_boardPtr->m_shapes)
        {
            r.setFillColor(sf::Color(49, 187, 191));
        }
        for(auto p : contactPos)
        {
            m_boardPtr->m_shapes[p].setFillColor(sf::Color::Yellow);
        }
    }
}

void Battleship::Rotate()
{
    if (m_state == STATES::IDLE)
    {
        shipSprite.rotate(90.f);
    }
}

void Battleship::Move(sf::Vector2f cord)
{
    if (m_state == STATES::IDLE)
    {
        shipSprite.setPosition(cord);
    }
}
