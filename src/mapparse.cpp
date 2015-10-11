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

    _tile.x = j["tiles"]["width"].get<int>();
    _tile.y = j["tiles"]["height"].get<int>();

    _tiles.x = j["map"]["width"].get<int>();
    _tiles.y = j["map"]["height"].get<int>();

    _map.x = _tiles.x * _tile.x;
    _map.y = _tiles.y * _tile.y;

    _tileset.x = j["tileset"]["width"].get<int>();
    _tileset.y = j["tileset"]["height"].get<int>();

    _tilesetImage = j["tileset"]["image"].get<std::string>();

    for(auto tile : j["floor"])
        _tiledata.emplace_back(tile.get<int>());

    generateTexture();
}

sf::Vector2i MapParse::getMapSize()
{
    return _map;
}

void MapParse::generateTexture()
{
    sf::Image imgTileset;
    imgTileset.loadFromFile("assets/" + _tilesetImage);

    _texture = new sf::Texture();
    _texture->create(_map.x, _map.y);

    for(unsigned int i = 0; i < _tiledata.size(); i++)
    {
        sf::Image imgTile;
        imgTile.create(_tile.x, _tile.y);

        int sx = ((_tiledata[i]-1) % _tileset.x) * _tile.x;
        int sy = ((_tiledata[i]-1) / _tileset.y) * _tile.y;

        std::cout << _tiledata[i] << ": " << sx << ":" << sy << std::endl;

        imgTile.copy(imgTileset, 0, 0, sf::IntRect(sx, sy, _tile.x, _tile.y), false);

        int tx = (i % _tiles.x) * _tile.x;
        int ty = (i / _tiles.y) * _tile.y;

        _texture->update(imgTile, tx, ty);
    }
}

void MapParse::draw(sf::RenderWindow* window)
{
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(_map.x, _map.y));
    bg.setTexture(_texture);
    
    window->draw(bg);
}

MapParse::~MapParse()
{
}
