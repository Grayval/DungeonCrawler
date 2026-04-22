// Player.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player
{
public:
    Player();
    void handleinput(float deltatime, Map& map);
    void draw(sf::RenderWindow& window);
    void update(float deltatime);

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    int health;
    int experience;
    int mana;
    int level;
};