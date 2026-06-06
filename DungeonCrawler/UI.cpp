#include "UI.hpp"



UI::UI()
{
    font.openFromFile("C:/Windows/Fonts/consola.ttf");
    levelText.emplace(font, "", 10);
    levelText->setFillColor(sf::Color::White);

	hpBarBackground.setSize(sf::Vector2f(32.f, 5.f));
	hpBarBackground.setFillColor(sf::Color(100, 100, 100));  // grau

	hpBar.setSize(sf::Vector2f(32.f, 5.f));
	hpBar.setFillColor(sf::Color::Green);
}

void UI::draw(Player& player, Enemy& enemy, sf::RenderWindow& window)
{
    
    float barWidth = (player.getHealth() / player.getMaxHealth()) * 32.f;
    hpBar.setSize(sf::Vector2f(barWidth, 5.f));

    
    sf::Vector2f pos = player.getPosition();
    hpBarBackground.setPosition(sf::Vector2f(pos.x, pos.y - 8.f));
    hpBar.setPosition(sf::Vector2f(pos.x, pos.y - 8.f));

    
    window.draw(hpBarBackground);
    window.draw(hpBar);


    float eBarWidth = (enemy.getHealth() / enemy.getMaxHealth()) * 32.f;
    hpBar.setSize(sf::Vector2f(eBarWidth, 5.f));


    sf::Vector2f ePos = enemy.getPosition();
    hpBarBackground.setPosition(sf::Vector2f(ePos.x, ePos.y - 8.f));
    hpBar.setPosition(sf::Vector2f(ePos.x, ePos.y - 8.f));

    window.draw(hpBarBackground);
    window.draw(hpBar);

    drawLevelText(pos, player.getLevel(), window);
    drawLevelText(ePos, enemy.getLevel(), window);
}

void UI::drawLevelText(const sf::Vector2f& pos, int level, sf::RenderWindow& window)
{
    levelText->setString("LV " + std::to_string(level));
    levelText->setPosition(sf::Vector2f(pos.x + 34.f, pos.y - 10.f));
    window.draw(*levelText);
}