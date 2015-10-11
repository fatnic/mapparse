#ifndef _MAPPARSE_HPP
#define _MAPPARSE_HPP

#include <string>
#include <SFML/Graphics.hpp>

class MapParse
{
public:
    MapParse();
    ~MapParse();
    void load(const std::string filename);
    sf::Vector2i getMapSize();
private:
    void generateTexture();
    std::string _tilesetImage;
    sf::Vector2i _tile;
    sf::Vector2i _tiles;
    sf::Vector2i _map;

    sf::Texture* _texture;
};

#endif
