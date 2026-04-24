#include <cstdlib>
#include "Player.hpp"



Player::Player()
{
	health = 100;
	mana = 100;
	experience = 0;
	level = 1;
	damage = 25;
	position = sf::Vector2f(160.f, 160.f);
	speed = 200.f;
	isInvincible = false;
	invincibilityTimer = 0.f;
	dead = false;
	respawnTimer = 0.f;
	shape.setSize(sf::Vector2f(32.f, 32.f));
	shape.setFillColor(sf::Color(148, 0, 211));
	shape.setPosition(position);
}

void Player::handleinput(float deltatime, Map& map)
{
	if (dead) return;

	sf::Vector2f oldPosition = position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		position.x -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		position.x += speed * deltatime;

	int gridX = (int) (position.x / 32);
	int gridY = (int) (position.y / 32);
	int gridX_2 = (int) (position.x + 31) / 32;
	int gridY_2 = (int) (position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || map.isWall(gridX_2, gridY) ||
		map.isWall(gridX, gridY_2) || map.isWall(gridX_2, gridY_2))
		position.x = oldPosition.x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		position.y -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		position.y += speed * deltatime;

	gridX = (int) (position.x / 32);
	gridY = (int) (position.y / 32);
	gridX_2 = (int) (position.x + 31) / 32;
	gridY_2 = (int) (position.y + 31) / 32;


	if (map.isWall(gridX, gridY) ||
		map.isWall(gridX_2, gridY) ||
		map.isWall(gridX, gridY_2) ||
		map.isWall(gridX_2, gridY_2))
		position = oldPosition;


}

void Player::takeDamage(int amount)
{
	health -= amount;
	if (health <= 0)
	{
		health = 0;
		dead = true;
		respawnTimer = 0.f;
		return;
	}
	isInvincible = true;
	invincibilityTimer = 0.f;
}

void Player::update(float deltaTime)
{
	shape.setPosition(position);

	if (isInvincible)
	{
		invincibilityTimer += deltaTime;

		
		if ((int)(invincibilityTimer * 10) % 2 == 0)
			shape.setFillColor(sf::Color(148, 0, 211));  
		else
			shape.setFillColor(sf::Color::Transparent);  

		if (invincibilityTimer >= 3.0f)
		{
			isInvincible = false;
			invincibilityTimer = 0.f;
			shape.setFillColor(sf::Color(148, 0, 211));
		}
	}

	if (dead)
	{
		respawnTimer += deltaTime;

		if ((int)(respawnTimer * 10) % 2 == 0)
			shape.setFillColor(sf::Color(148, 0, 211));
		else
			shape.setFillColor(sf::Color::Transparent);

		if (respawnTimer >= 3.0f)
			respawn();
	}
}

void Player::respawn()
{
	health = 100;
	dead = false;
	respawnTimer = 0.f;
	isInvincible = false;
	invincibilityTimer = 0.f;
	position = sf::Vector2f(160.f, 160.f);
	shape.setFillColor(sf::Color(148, 0, 211));
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}