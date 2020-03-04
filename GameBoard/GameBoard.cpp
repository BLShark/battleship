#include "GameBoard.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace
{
    const sf::Color CellColor(49, 187, 191);
    const int board_size = 10;
    const int m_size = 50;
    const int m_thickness = 2;
}

void GameBoard::Init()
{
    const sf::Vector2f initialPos = {265, 10};
    sf::Vector2f pos = initialPos + sf::Vector2f(m_thickness, m_thickness);

    m_cells.resize(board_size, std::vector<Cell>(board_size));

    for(int y = 0; y < board_size; y++)
    {
        for(int x = 0; x < board_size; x++)
        {
            auto& shape = m_cells[y][x].shape;
            shape.setFillColor(CellColor);
            shape.setSize(sf::Vector2f(m_size, m_size));
            shape.setPosition(pos);
            pos.x += m_size + m_thickness;
        }
        pos.x = initialPos.x + m_thickness;
        pos.y += m_size + m_thickness;
    }

    m_shipSelector.Init({2, 3, 3, 4, 5});
}

void GameBoard::Draw(sf::RenderWindow &window)
{
    m_shipSelector.Draw(window);
    for(auto& row : m_cells)
    {
        for(auto& cell : row)
        {
            cell.shape.setFillColor(cell.onFocus ? sf::Color::Yellow : CellColor);
            if(cell.occupied)
            {
                cell.shape.setFillColor(sf::Color::Red);
            }
            window.draw(cell.shape);
        }
    }
}

void GameBoard::OnInputEvent(const sf::Event& event, const sf::RenderWindow& window)
{

    if(m_shipSelector.IsShipSelected())
    {
        static int rotation = 0;
        static std::vector<sf::Vector2i> positions;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            rotation += 90;
            if(rotation == 360)
            {
                rotation = 0;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            positions.resize(m_shipSelector.GetSelectedShipSize(), sf::Vector2i());
            positions[0] = sf::Mouse::getPosition(window);
            for(int i = 1; i < positions.size(); i++)
            {
                int x = positions[i-1].x;
                int y = positions[i-1].y;
                if(rotation == 0 || rotation == 180)
                {
                    x += m_size + m_thickness;
                }
                else if(rotation == 90 || rotation == 270)
                {
                    y += m_size + m_thickness;
                }
                positions[i] = {x,y};
            }

            m_focusedCells.clear();
            for(auto& row : m_cells)
            {
                for(auto& cell : row)
                {
                    cell.onFocus = false;

                    for(auto p : positions)
                    {
                        if(cell.shape.getGlobalBounds().contains(p.x, p.y))
                        {
                            cell.onFocus = true;
                            m_focusedCells.push_back(&cell);
                        }
                    }
                }
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            bool isValid = true;
            if(m_focusedCells.size() < m_shipSelector.GetSelectedShipSize())
            {
                isValid = false;
            }
            else
            {
                for(auto cell : m_focusedCells)
                {
                    if(cell->occupied)
                    {
                        isValid = false;
                        break;
                    }
                }
            }

            for(auto cell : m_focusedCells)
            {
                cell->onFocus = false;
                if(isValid)
                {
                    cell->occupied = true;
                }
            }

            if (isValid)
                m_shipSelector.DeactivateShip();
        }
    }
    m_shipSelector.OnInputEvent(event, window);
}
