#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

class ResourceMgr
{
public:
    ResourceMgr();

    sf::Font font;
    sf::Texture& GetTexture(const std::string& id);
private:
    std::map<std::string, sf::Texture> m_textures;
};
ResourceMgr& GetResourceMgr();
