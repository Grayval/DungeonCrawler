#include <optional>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "UI.hpp"
#include "Combatsys.hpp"



int main()
{
    sf::Clock clock;
    Player Player;
    Enemy Enemy;
    Map map;
    UI ui;
    CombatSys CombatSys;
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Crawler");
    
    bool playerAttacked = false;

    while (window.isOpen())
    {
        playerAttacked = false;

        float deltatime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::KeyPressed>())
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                    playerAttacked = true;

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (playerAttacked)
        {
            sf::Vector2f diff = Player.getPosition() - Enemy.e_GetPosition();
            float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

            if (distance < 64.f && !Enemy.e_GetIsInvincible())
                Enemy.takeDamage(Player.getDamage());
        }

        Player.handleinput(deltatime, map);
        Enemy.enemy_ai(Player.getPosition(), deltatime, map);
        CombatSys.checkCombat(Player, Enemy, deltatime, playerAttacked);
        
        
        sf::Vector2f pPos = Player.getPosition();
        sf::Vector2f ePos = Enemy.e_GetPosition();

        if (Player.get_shape().findIntersection(Enemy.get_e_Shape())) 
        {
            sf::Vector2f diff = pPos - ePos;
            float length = sqrt(diff.x * diff.x + diff.y * diff.y);
            if (length != 0)
                diff /= length;

            sf::Vector2f newPos = pPos + diff * 32.f;

            
            int gridX = (int)(newPos.x / 32);
            int gridY = (int)(newPos.y / 32);
            int gridX2 = (int)((newPos.x + 31) / 32);
            int gridY2 = (int)((newPos.y + 31) / 32);

            if (!map.isWall(gridX, gridY) && !map.isWall(gridX2, gridY) &&
                !map.isWall(gridX, gridY2) && !map.isWall(gridX2, gridY2))
                Player.setPosition(newPos);

            Enemy.e_SetPosition(ePos - diff * 32.f, map);
        }

        Player.update(deltatime);
        Enemy.e_Update(deltatime);


        window.clear(sf::Color::Black);
        map.draw(window);
        Enemy.e_Draw(window);
        Player.draw(window);
        ui.draw(Player, Enemy, window);
        
        window.display();
    }

    return 0;
}