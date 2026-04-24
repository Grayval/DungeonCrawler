#include "UI.hpp"



UI::UI()
{
	maxHealth = 100;

	hpBarBackground.setSize(sf::Vector2f(32.f, 5.f));
	hpBarBackground.setFillColor(sf::Color(100, 100, 100));  // grau

	hpBar.setSize(sf::Vector2f(32.f, 5.f));
	hpBar.setFillColor(sf::Color::Green);
}

void UI::draw(Player& health, Enemy& e_Health, sf::RenderWindow& window)
{
    
    float barWidth = (health.getHealth() / (float)maxHealth) * 32.f;
    hpBar.setSize(sf::Vector2f(barWidth, 5.f));

    
    sf::Vector2f pos = health.getPosition();
    hpBarBackground.setPosition(sf::Vector2f(pos.x, pos.y - 8.f));
    hpBar.setPosition(sf::Vector2f(pos.x, pos.y - 8.f));

    
    window.draw(hpBarBackground);
    window.draw(hpBar);


    float e_BarWidth = (e_Health.e_GetHealth() / (float)maxHealth) * 32.f;
    hpBar.setSize(sf::Vector2f(e_BarWidth, 5.f));


    sf::Vector2f e_Pos = e_Health.e_GetPosition();
    hpBarBackground.setPosition(sf::Vector2f(e_Pos.x, e_Pos.y - 8.f));
    hpBar.setPosition(sf::Vector2f(e_Pos.x, e_Pos.y - 8.f));

    window.draw(hpBarBackground);
    window.draw(hpBar);
}