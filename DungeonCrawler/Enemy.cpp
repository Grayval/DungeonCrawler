#include <cstdlib>
#include "Enemy.hpp"
#include "Map.hpp"

Enemy::Enemy()
{
	e_Health = 100;
	e_Damage = 25;
	e_Speed = 100.f;
	e_IsInvincible = false;
	e_InvincibilityTimer = 0.f;
	e_IsDead = false;
	e_RespawnTimer = 0.f;
	e_Position = sf::Vector2f(500.f, 500.f);

	e_Shape.setSize(sf::Vector2f(32.f, 32.f));
	e_Shape.setFillColor(sf::Color::Cyan);
	e_Shape.setPosition(e_Position);
}

void Enemy::takeDamage(int amount)
{
	e_Health -= amount;
	if (e_Health <= 0)
	{
		e_Health = 0;
		e_IsDead = true;
		e_RespawnTimer = 0.f;
		return;
	}
	e_IsInvincible = true;
	e_InvincibilityTimer = 0.f;
}

void Enemy::e_Update(float deltaTime)
{
	e_Shape.setPosition(e_Position);

	if (e_IsInvincible)
	{
		e_InvincibilityTimer += deltaTime;

		if ((int)(e_InvincibilityTimer * 10) % 2 == 0)
			e_Shape.setFillColor(sf::Color::Cyan);
		else
			e_Shape.setFillColor(sf::Color::Transparent);

		if (e_InvincibilityTimer >= 3.0f)
		{
			e_IsInvincible = false;
			e_InvincibilityTimer = 0.f;
			e_Shape.setFillColor(sf::Color::Cyan);
		}
	}

	if (e_IsDead)
	{
		e_RespawnTimer += deltaTime;

		if ((int)(e_RespawnTimer * 10) % 2 == 0)
			e_Shape.setFillColor(sf::Color::Cyan);
		else
			e_Shape.setFillColor(sf::Color::Transparent);

		if (e_RespawnTimer >= 3.0f)
			e_Respawn();
	}
}

void Enemy::e_Draw(sf::RenderWindow& window)
{
	window.draw(e_Shape);
}

void Enemy::e_Respawn()
{
	e_Health = 100;
	e_IsDead = false;
	e_RespawnTimer = 0.f;
	e_IsInvincible = false;
	e_InvincibilityTimer = 0.f;

	int randX = (rand() % (GRID_WIDTH - 2)) + 1;
	int randY = (rand() % (GRID_HEIGHT - 2)) + 1;
	e_Position = sf::Vector2f(randX * 32.f, randY * 32.f);

	e_Shape.setFillColor(sf::Color::Cyan);
}

void Enemy::enemy_ai(sf::Vector2f playerPosition, float deltaTime, Map& map)
{
	if (e_IsDead) return;

	sf::Vector2f e_OldPosition = e_Position;

	sf::Vector2f direction = playerPosition - e_Position;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 1.0f)
		direction /= length;

	e_Position.x += direction.x * e_Speed * deltaTime;

	int gridX = (int)(e_Position.x / 32);
	int gridY = (int)(e_Position.y / 32);
	int gridX2 = (int)(e_Position.x + 31) / 32;
	int gridY2 = (int)(e_Position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || map.isWall(gridX2, gridY) ||
		map.isWall(gridX, gridY2) || map.isWall(gridX2, gridY2))
		e_Position.x = e_OldPosition.x;

	e_Position.y += direction.y * e_Speed * deltaTime;

	gridX = (int)(e_Position.x / 32);
	gridY = (int)(e_Position.y / 32);
	gridX2 = (int)(e_Position.x + 31) / 32;
	gridY2 = (int)(e_Position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || 
		map.isWall(gridX2, gridY) ||
		map.isWall(gridX, gridY2) || 
		map.isWall(gridX2, gridY2))

		e_Position.y = e_OldPosition.y;
}
void Enemy::e_SetPosition(sf::Vector2f pos, Map& map)
{
	int gridX = (int)(pos.x / 32);
	int gridY = (int)(pos.y / 32);
	int gridX2 = (int)((pos.x + 31) / 32);
	int gridY2 = (int)((pos.y + 31) / 32);

	if (!map.isWall(gridX, gridY) && !map.isWall(gridX2, gridY) &&
		!map.isWall(gridX, gridY2) && !map.isWall(gridX2, gridY2))
		e_Position = pos;
}