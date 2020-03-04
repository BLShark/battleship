#include "Ship.h"
#include "ResourceMgr.h"

void Ship::Init(const std::string &resourceId, size_t sz)
{
    sprite.setTexture(GetResourceMgr().GetTexture(resourceId));
    size = sz;
}

void Ship::Draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
