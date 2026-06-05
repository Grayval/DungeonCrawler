#include "Combatsys.hpp"
#include "Player.hpp"
#include "Enemy.hpp"




CombatSys::CombatSys()
{
	damageTimer = 0.f;
    playerAttackTimer = 0.5f;
    playerDamageTimer = 0.f;
}

void CombatSys::checkCombat(Player& player, Enemy& enemy, float deltaTime, bool playerAttacked)
{
    damageTimer += deltaTime;

    if (player.getShape().findIntersection(enemy.getShape()))
    {
        if (damageTimer >= 3.0f && !player.getIsInvincible())
        {
            player.takeDamage(enemy.getDamage());
            damageTimer = 0.f;
        }
    }

    playerAttackTimer += deltaTime;

    if (playerAttacked)
    {
        if (player.getShape().findIntersection(enemy.getShape()))
        {
            if (!enemy.getIsInvincible())
            {
                enemy.takeDamage(player.getDamage());
            }
        }
    }
}

