#include "Ship.h"
#include "ResourceMgr.h"

void Ship::Init(const std::string &resourceId, size_t sz)
{
    m_sprite.setTexture(GetResourceMgr().GetTexture(resourceId));
    m_size = sz;
}

void Ship::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

void Ship::Rotate()
{
    m_rotation += 90;
    if(m_rotation == 360)
    {
        m_rotation = 0;
    }
}

int Ship::GetSize() const
{
    return m_size;
}

sf::Sprite &Ship::GetSprite()
{
    return m_sprite;
}

int Ship::GetRotation() const
{
    return m_rotation;
}
