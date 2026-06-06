#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>



class Enemy
{
	public:
		Enemy();
		void enemyAi(sf::Vector2f playerPosition, float deltaTime, Map& map);
		void draw(sf::RenderWindow& window);
		void update(float deltatime);
		void takeDamage(int amount);
		float getHealth() { return health; }
		sf::Vector2f getPosition() { return position; }
		sf::FloatRect getShape() { return shape.getGlobalBounds(); }
		int getDamage() { return damage; }
		void setPosition(sf::Vector2f pos, Map& map);
		bool getIsInvincible() { return isInvincible; }
		bool getDead() { return health <= 0; }
		void respawn();
		float getMaxHealth();
		int getLevel();


	private:
		sf::RectangleShape shape;
		sf::Vector2f position;
		float speed;
		float health;
		float maxHealth;
		int level;
		int damage;
		bool isInvincible;
		float invincibilityTimer;
		float respawnTimer;
		bool isDead;
};
