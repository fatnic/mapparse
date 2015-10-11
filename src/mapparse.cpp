#include "mapparse.hpp"
#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

MapParse::MapParse()
{}

void MapParse::load(const std::string filename)
{
    std::ifstream _file(filename);
    std::string stringbuff(std::istreambuf_iterator<char>(_file), {});
    auto j = json::parse(stringbuff);

    // Size of each tile
    _tile.x = j["tilewidth"].get<int>();
    _tile.y = j["tileheight"].get<int>();

    // Amount of tiles x/y for map
    _tiles.x = j["width"].get<int>();
    _tiles.y = j["height"].get<int>();

    // Resolution of map
    _map.x = _tiles.x * _tile.x;
    _map.y = _tiles.y * _tile.y;

    _tilesetImage = j["tilesets"][0]["image"].get<std::string>();
    
}

sf::Vector2i MapParse::getMapSize()
{
    return _map;
}

void MapParse::generateTexture()
{
}

MapParse::~MapParse()
{
    sf::Image imgTileset;
    imgTileset.loadFromFile(_tilesetImage);


}
