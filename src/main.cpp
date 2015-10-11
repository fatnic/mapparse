#include <SFML/Graphics.hpp>
#include "mapparse.hpp"

int main()
{
    MapParse mp;
    mp.load("assets/map.json");

    sf::RenderWindow window(sf::VideoMode(mp.getMapSize().x, mp.getMapSize().y), "GameWindow");
    
    while(window.isOpen())
    {
        sf::Event event;
        if(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(64,64,64));
        mp.draw(&window);
        window.display();
    }
    return 0;
}
