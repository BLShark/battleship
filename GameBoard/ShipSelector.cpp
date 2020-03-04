#include "ShipSelector.h"
#include "ResourceMgr.h"

void ShipSelector::Init(const std::vector<int>& shipSizes)
{
    int xPos = 10;
    int yPos = 10;
//    for(auto size : shipSizes)
    {
        Ship ship;
        ship.sprite.move(230, 30);
        ship.sprite.rotate(90.0f);
        ship.Init("ship2", 3);
        m_allShips.emplace_back(std::move(ship));

        yPos += 40;
    }
}

void ShipSelector::Draw(sf::RenderWindow &window)
{
    for(auto& ship : m_allShips)
    {
        ship.Draw(window);
    }
}

void ShipSelector::OnInputEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if(m_selectedShip == nullptr &&
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto p = sf::Mouse::getPosition(window);
        for(auto& ship : m_allShips)
        {
            if(ship.status != ShipStatus::RESERVED &&
                ship.sprite.getGlobalBounds().contains(p.x, p.y))
            {
                m_selectedShip = &ship;
                m_selectedShip->sprite.setColor(sf::Color::Green);
                break;
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(nullptr != m_selectedShip)
        {
            if (m_selectedShip->status == ShipStatus::IDLE){
                m_selectedShip->sprite.setColor(sf::Color::White);
            }
            else if (m_selectedShip->status == ShipStatus::RESERVED) {
                m_selectedShip->sprite.setColor(sf::Color::Red);
            }
            m_selectedShip = nullptr;
        }
    }
}

bool ShipSelector::IsShipSelected()
{
    return (m_selectedShip != nullptr);
}

uint8_t ShipSelector::GetSelectedShipSize()
{
    if (m_selectedShip != nullptr)
        return m_selectedShip->sprite.getTextureRect().width / 30;

    return 0;
}

void ShipSelector::DeactivateShip()
{
    if (m_selectedShip == nullptr)
        return;

    m_selectedShip->status = ShipStatus::RESERVED;
}
