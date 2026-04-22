#include "Player.hpp"



Player::Player()
{
	health = 100;
	mana = 100;
	experience = 0;
	level = 1;
	position = sf::Vector2f(160.f, 160.f);
	speed = 200.f;
	shape.setSize(sf::Vector2f(32.f, 32.f));
	shape.setFillColor(sf::Color(148, 0, 211));
	shape.setPosition(position);
}

void Player::handleinput(float deltatime, Map& map)
{
	sf::Vector2f oldPosition = position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		position.x -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		position.x += speed * deltatime;

	int gridX = position.x / 32;
	int gridY = position.y / 32;
	int gridX_2 = (position.x + 31) / 32;
	int gridY_2 = (position.y + 31) / 32;

	if (map.isWall(gridX, gridY) || map.isWall(gridX_2, gridY) ||
		map.isWall(gridX, gridY_2) || map.isWall(gridX_2, gridY_2))
		position.x = oldPosition.x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		position.y -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		position.y += speed * deltatime;

	gridX = position.x / 32;
	gridY = position.y / 32;
	gridX_2 = (position.x + 31) / 32;
	gridY_2 = (position.y + 31) / 32;


	if (map.isWall(gridX, gridY) ||
		map.isWall(gridX_2, gridY) ||
		map.isWall(gridX, gridY_2) ||
		map.isWall(gridX_2, gridY_2))
		position = oldPosition;


}

void Player::update(float deltaTime)
{
	shape.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}