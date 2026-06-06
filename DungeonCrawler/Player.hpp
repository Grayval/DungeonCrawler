#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player
{
public:
    Player();
    void handleInput(float deltatime, Map& map);
    void draw(sf::RenderWindow& window);
    void update(float deltatime);
    sf::Vector2f getPosition() { return position; }
    void takeDamage(int amount);
    float getHealth() { return health; }
    sf::FloatRect getShape() { return shape.getGlobalBounds(); }
    int getDamage() { return damage; }
    void setPosition(sf::Vector2f pos) { position = pos; }
    bool getIsInvincible() { return isInvincible; }
    bool getDead() { return dead; }
    void respawn();
    int getLevel() const;
    float getMaxHealth();

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    float health;
    float maxHealth;
    int experience;
    int mana;
    int level;
    int damage;
    bool isInvincible;
    float invincibilityTimer;
    bool dead;
    float respawnTimer;
};