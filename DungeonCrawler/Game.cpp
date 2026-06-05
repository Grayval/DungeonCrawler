#include "Game.hpp"
#include <cmath>

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Dungeon Crawler")
    , m_deltatime(0.f)
    , m_playerAttacked(false)
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
        m_playerAttacked = false;
        m_deltatime = m_clock.restart().asSeconds();

        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::KeyPressed>())
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                m_playerAttacked = true;

        if (event->is<sf::Event::Closed>())
            m_window.close();
    }
}

void Game::update()
{
    if (m_playerAttacked)
    {
        sf::Vector2f diff = m_player.getPosition() - m_enemy.getPosition();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        if (distance < 64.f && !m_enemy.getIsInvincible())
            m_enemy.takeDamage(m_player.getDamage());
    }

    m_player.handleInput(m_deltatime, m_map);
    m_enemy.enemyAi(m_player.getPosition(), m_deltatime, m_map);
    m_combatSys.checkCombat(m_player, m_enemy, m_deltatime, m_playerAttacked);

    resolveCollision();

    m_player.update(m_deltatime);
    m_enemy.update(m_deltatime);
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_map.draw(m_window);
    m_enemy.draw(m_window);
    m_player.draw(m_window);
    m_ui.draw(m_player, m_enemy, m_window);
    m_window.display();
}

void Game::resolveCollision()
{
    if (!m_player.getShape().findIntersection(m_enemy.getShape()))
        return;

    sf::Vector2f pPos = m_player.getPosition();
    sf::Vector2f ePos = m_enemy.getPosition();

    sf::Vector2f diff = pPos - ePos;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    if (length != 0)
        diff /= length;

    sf::Vector2f newPos = pPos + diff * 32.f;

    int gridX = (int)(newPos.x / 32);
    int gridY = (int)(newPos.y / 32);
    int gridX2 = (int)((newPos.x + 31) / 32);
    int gridY2 = (int)((newPos.y + 31) / 32);

    if (!m_map.isWall(gridX, gridY) && !m_map.isWall(gridX2, gridY) &&
        !m_map.isWall(gridX, gridY2) && !m_map.isWall(gridX2, gridY2))
        m_player.setPosition(newPos);

    m_enemy.setPosition(ePos - diff * 32.f, m_map);
}