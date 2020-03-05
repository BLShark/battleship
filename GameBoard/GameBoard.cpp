#include "GameBoard.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace
{
    const sf::Color CellColor(49, 187, 191);
    const sf::Color OccupiedColor(47,151,239);
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

    m_shipSelector.Init();
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
                cell.shape.setFillColor(OccupiedColor);
            }
            window.draw(cell.shape);
        }
    }

    for(auto& ship : m_ships)
    {
        window.draw(ship.GetSprite());
    }
}

void GameBoard::OnInputEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    m_shipSelector.OnInputEvent(event, window);
    auto ship = m_shipSelector.GetSelectedShip();
    if(nullptr == ship)
    {
        return;
    }

    auto positions = GetPositions(window, ship);
    FindFocusedCells(positions);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        TryToAddShipToBoard(ship);
    }
}

void GameBoard::TryToAddShipToBoard(Ship *ship)
{
    bool isValid = true;
    if(m_focusedCells.size() < ship->GetSize())
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
    {
        m_shipSelector.DeactivateShip();
        m_ships.emplace_back(*ship);
        auto& sprite = m_ships.back().GetSprite();

        sf::FloatRect boundingBox = {INT32_MAX, INT32_MAX, 0, 0};
        for(auto cell : m_focusedCells)
        {
            boundingBox.left = std::min(boundingBox.left, cell->shape.getPosition().x);
            boundingBox.width = std::max(boundingBox.width, cell->shape.getPosition().x + cell->shape.getSize().x);

            boundingBox.top = std::min(boundingBox.top, cell->shape.getPosition().y);
            boundingBox.height = std::max(boundingBox.height, cell->shape.getPosition().y + cell->shape.getSize().y);
        }
        boundingBox.width -= boundingBox.left;
        boundingBox.height -= boundingBox.top;

        sprite.setPosition(boundingBox.left + (boundingBox.width / 2),
                           boundingBox.top + (boundingBox.height / 2));
        sprite.setRotation(ship->GetRotation());
        sprite.setColor(sf::Color::White);
    }
}

void GameBoard::FindFocusedCells(const std::vector<sf::Vector2i> &positions)
{
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

std::vector<sf::Vector2i> GameBoard::GetPositions(const sf::RenderWindow &window, Ship *ship) const
{
    auto rotation = ship->GetRotation();
    std::vector<sf::Vector2i> positions;
    positions.resize(ship->GetSize(), sf::Vector2i());
    positions[0] = sf::Mouse::getPosition(window);
    for(int i = 1; i < positions.size(); i++)
    {
        int x = positions[i-1].x;
        int y = positions[i-1].y;
        if(rotation == 0 || rotation == 180)
        {
            y += m_size + m_thickness;
        }
        else if(rotation == 90 || rotation == 270)
        {
            x += m_size + m_thickness;
        }
        positions[i] = {x,y};
    }
    return positions;
}
