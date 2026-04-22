#include <optional>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Map.hpp"

int main()
{
    sf::Clock clock;
    Player player;
    Map map;
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Crawler");

    while (window.isOpen())
    {
        float deltatime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.handleinput(deltatime, map);
        player.update(deltatime);


        window.clear(sf::Color::Black);
        map.draw(window);
        player.draw(window);
        window.display();
    }

    return 0;
}