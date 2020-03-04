#include "ResourceMgr.h"

ResourceMgr::ResourceMgr()
{
    font.loadFromFile("../battleship/Assets/Arial.ttf");
    m_textures["ship1"].loadFromFile("../battleship/Assets/ship1.png");
    m_textures["ship2"].loadFromFile("../battleship/Assets/ship2.png");
    m_textures["ship3"].loadFromFile("../battleship/Assets/ship3.png");
    m_textures["ship4"].loadFromFile("../battleship/Assets/ship4.png");
    m_textures["ship5"].loadFromFile("../battleship/Assets/ship5.png");
}

sf::Texture& ResourceMgr::GetTexture(const std::string &id)
{
    static sf::Texture empty;

    auto iter = m_textures.find(id);
    if(iter != m_textures.end())
    {
        return iter->second;
    }

    return empty;
}

ResourceMgr &GetResourceMgr()
{
    static ResourceMgr rssMgr;
    return rssMgr;
}
