#include "Game.hpp"
#include <cmath>

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Dungeon Crawler")
    , deltatime(0.f)
    , playerAttacked(false)
{
}

void Game::run()
{
    while (window.isOpen())
    {
        playerAttacked = false;
        deltatime = clock.restart().asSeconds();

        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::KeyPressed>())
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                playerAttacked = true;

        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::update()
{
    if (playerAttacked)
    {
        sf::Vector2f diff = player.getPosition() - enemy.getPosition();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        if (distance < 64.f && !enemy.getIsInvincible())
            enemy.takeDamage(player.getDamage());
    }

    player.handleInput(deltatime, map);
    enemy.enemyAi(player.getPosition(), deltatime, map);
    combatSys.checkCombat(player, enemy, deltatime, playerAttacked);

    resolveCollision();

    player.update(deltatime);
    enemy.update(deltatime);
}

void Game::render()
{
    window.clear(sf::Color::Black);
    map.draw(window);
    enemy.draw(window);
    player.draw(window);
    ui.draw(player, enemy, window);
    window.display();
}

void Game::resolveCollision()
{
    if (!player.getShape().findIntersection(enemy.getShape()))
        return;

    sf::Vector2f pPos = player.getPosition();
    sf::Vector2f ePos = enemy.getPosition();

    sf::Vector2f diff = pPos - ePos;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    if (length != 0)
        diff /= length;

    sf::Vector2f newPos = pPos + diff * 32.f;

    int gridX = (int)(newPos.x / 32);
    int gridY = (int)(newPos.y / 32);
    int gridX2 = (int)((newPos.x + 31) / 32);
    int gridY2 = (int)((newPos.y + 31) / 32);

    if (!map.isWall(gridX, gridY) && !map.isWall(gridX2, gridY) &&
        !map.isWall(gridX, gridY2) && !map.isWall(gridX2, gridY2))
        player.setPosition(newPos);

    enemy.setPosition(ePos - diff * 32.f, map);
}