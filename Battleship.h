#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Board.h"

class Battleship
{
    enum STATES {IDLE, ALIVE, DEAD};

public:
    void Init(const std::string& image, board::Board* board, int boardSize);
    void Draw(sf::RenderWindow& window);
    void SetPossition(sf::Vector2f cord);
    void OnEvent(const sf::Event& e, sf::RenderWindow* window);

    sf::Sprite shipSprite;
    sf::Texture shipTexture;

    bool isPressed = false;
    STATES m_state = STATES::IDLE;
private:
    void Rotate();
    void Move(sf::Vector2f cord);
    board::Board* m_boardPtr = nullptr;

    int m_boardSize = 0;
};
