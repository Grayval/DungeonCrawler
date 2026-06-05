#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Map.hpp"
#include "UI.hpp"
#include "Combatsys.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void resolveCollision();

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_deltatime;
    bool m_playerAttacked;

    Player m_player;
    Enemy m_enemy;
    Map m_map;
    UI m_ui;
    CombatSys m_combatSys;
};