#include <cstdlib>
#include "Enemy.hpp"
#include "Map.hpp"

Enemy::Enemy()
{
	health = 100;
	damage = 25;
	speed = 100.f;
	isInvincible = false;
	invincibilityTimer = 0.f;
	isDead = false;
	respawnTimer = 0.f;
	position = sf::Vector2f(500.f, 500.f);

	shape.setSize(sf::Vector2f(32.f, 32.f));
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition(position);
}

void Enemy::takeDamage(int amount)
{
	health -= amount;
	if (health <= 0)
	{
		health = 0;
		isDead = true;
		respawnTimer = 0.f;
		return;
	}
	isInvincible = true;
	invincibilityTimer = 0.f;
}

void Enemy::update(float deltaTime)
{
	shape.setPosition(position);

	if (isInvincible)
	{
		invincibilityTimer += deltaTime;

		if ((int)(invincibilityTimer * 10) % 2 == 0)
			shape.setFillColor(sf::Color::Cyan);
		else
			shape.setFillColor(sf::Color::Transparent);

		if (invincibilityTimer >= 3.0f)
		{
			isInvincible = false;
			invincibilityTimer = 0.f;
			shape.setFillColor(sf::Color::Cyan);
		}
	}

	if (isDead)
	{
		respawnTimer += deltaTime;

		if ((int)(respawnTimer * 10) % 2 == 0)
			shape.setFillColor(sf::Color::Cyan);
		else
			shape.setFillColor(sf::Color::Transparent);

		if (respawnTimer >= 3.0f)
			respawn();
	}
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Enemy::respawn()
{
	health = 100;
	isDead = false;
	respawnTimer = 0.f;
	isInvincible = false;
	invincibilityTimer = 0.f;

	int randX = (rand() % (Map::GRID_WIDTH - 2)) + 1;
	int randY = (rand() % (Map::GRID_HEIGHT - 2)) + 1;
	position = sf::Vector2f(randX * 32.f, randY * 32.f);

	shape.setFillColor(sf::Color::Cyan);
}

void Enemy::enemyAi(sf::Vector2f playerPosition, float deltaTime, Map& map)
{
	if (isDead) return;

	sf::Vector2f oldPosition = position;

	sf::Vector2f direction = playerPosition - position;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 1.0f)
		direction /= length;

	position.x += direction.x * speed * deltaTime;

	int gridX = (int)(position.x / 32);
	int gridY = (int)(position.y / 32);
	int gridX2 = (int)(position.x + 31) / 32;
	int gridY2 = (int)(position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || map.isWall(gridX2, gridY) ||
		map.isWall(gridX, gridY2) || map.isWall(gridX2, gridY2))
		position.x = oldPosition.x;

	position.y += direction.y * speed * deltaTime;

	gridX = (int)(position.x / 32);
	gridY = (int)(position.y / 32);
	gridX2 = (int)(position.x + 31) / 32;
	gridY2 = (int)(position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || 
		map.isWall(gridX2, gridY) ||
		map.isWall(gridX, gridY2) || 
		map.isWall(gridX2, gridY2))

		position.y = oldPosition.y;
}
void Enemy::setPosition(sf::Vector2f pos, Map& map)
{
	int gridX = (int)(pos.x / 32);
	int gridY = (int)(pos.y / 32);
	int gridX2 = (int)((pos.x + 31) / 32);
	int gridY2 = (int)((pos.y + 31) / 32);

	if (!map.isWall(gridX, gridY) && !map.isWall(gridX2, gridY) &&
		!map.isWall(gridX, gridY2) && !map.isWall(gridX2, gridY2))
		position = pos;
}