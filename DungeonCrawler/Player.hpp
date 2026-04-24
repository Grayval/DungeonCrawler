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
    sf::Vector2f getPosition() { return position; }
    void takeDamage(int amount);
    int getHealth() { return health; }
    sf::FloatRect get_shape() { return shape.getGlobalBounds(); }
    int getDamage() { return damage; }
    void setPosition(sf::Vector2f pos) { position = pos; }
    bool getIsInvincible() { return isInvincible; }
    bool GetDead() { return dead; }
    void respawn();

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    int health;
    int experience;
    int mana;
    int level;
    int damage;
    bool isInvincible;
    float invincibilityTimer;
    bool dead;
    float respawnTimer;
};