#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>



class Enemy
{
	public:
		Enemy();
		void enemy_ai(sf::Vector2f playerPosition, float deltaTime, Map& map);
		void e_Draw(sf::RenderWindow& window);
		void e_Update(float deltatime);
		void takeDamage(int amount);
		int e_GetHealth() { return e_Health; }
		sf::Vector2f e_GetPosition() { return e_Position; }
		sf::FloatRect get_e_Shape() { return e_Shape.getGlobalBounds(); }
		int getDamage() { return e_Damage; }
		void e_SetPosition(sf::Vector2f pos, Map& map);
		bool e_GetIsInvincible() { return e_IsInvincible; }
		bool e_GetDead() { return e_Health <= 0; }
		void e_Respawn();


	private:
		sf::RectangleShape e_Shape;
		sf::Vector2f e_Position;
		float e_Speed;
		int e_Health;
		int e_Damage;
		bool e_IsInvincible;
		float e_InvincibilityTimer;
		float e_RespawnTimer;
		bool e_IsDead;
};
