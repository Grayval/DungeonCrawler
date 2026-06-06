#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class UI 
{
public:
	UI();
	void draw(Player& player, Enemy& enemy, sf::RenderWindow& window);
	void drawLevelText(const sf::Vector2f &pos, int level, sf::RenderWindow & window);

private:
	sf::RectangleShape hpBarBackground;
	sf::RectangleShape hpBar;
	std::optional<sf::Text> levelText;
	sf::Font	font;
};