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

    sf::RenderWindow window;
    sf::Clock clock;
    float deltatime;
    bool playerAttacked;

    Player player;
    Enemy enemy;
    Map map;
    UI ui;
    CombatSys combatSys;
};