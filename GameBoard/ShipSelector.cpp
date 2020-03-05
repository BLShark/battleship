#include "ShipSelector.h"
#include "ResourceMgr.h"

void ShipSelector::Init()
{
    std::map<std::string, int> shipSizes =
    {
        {"ship1", 5},
        {"ship2", 4},
        {"ship3", 3},
        {"ship4", 3},
        {"ship5", 2},
    };

    int xPos = 140;
    int yPos = 60;
    for(const auto& kvp : shipSizes)
    {
        Ship ship;
        ship.Init(kvp.first, kvp.second);

        auto& sprite = ship.GetSprite();
        sprite.setPosition(xPos, yPos);
        sprite.setRotation(90.0f);
        sprite.setOrigin(float(sprite.getTextureRect().width) / 2,
                         float(sprite.getTextureRect().height) / 2);
        m_allShips.emplace_back(std::move(ship));

        yPos += 80;
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
    if(m_selectedShip == nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto p = sf::Mouse::getPosition(window);
        for(auto& ship : m_allShips)
        {
            if(ship.status != ShipStatus::RESERVED &&
                ship.GetSprite().getGlobalBounds().contains(p.x, p.y))
            {
                m_selectedShip = &ship;
                m_selectedShip->GetSprite().setColor(sf::Color::Green);
                break;
            }
        }
    }
    else if(m_selectedShip != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        m_selectedShip->Rotate();
    }
}

Ship* ShipSelector::GetSelectedShip()
{
    return m_selectedShip;
}

void ShipSelector::DeactivateShip()
{
    if (m_selectedShip == nullptr)
    {
        return;
    }

    m_selectedShip->status = ShipStatus::RESERVED;
    if(nullptr != m_selectedShip)
    {
        if (m_selectedShip->status == ShipStatus::IDLE){
            m_selectedShip->GetSprite().setColor(sf::Color::White);
        }
        else if (m_selectedShip->status == ShipStatus::RESERVED) {
            m_selectedShip->GetSprite().setColor(sf::Color::Red);
        }
        m_selectedShip = nullptr;
    }
}
