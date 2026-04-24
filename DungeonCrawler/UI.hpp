#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class UI 
{
public:
	UI();
	void draw(Player& health, Enemy& e_Health, sf::RenderWindow& window);

private:
	int maxHealth;
	sf::RectangleShape hpBarBackground;
	sf::RectangleShape hpBar;
};