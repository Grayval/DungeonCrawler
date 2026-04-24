#include "Combatsys.hpp"
#include "Player.hpp"
#include "Enemy.hpp"




CombatSys::CombatSys()
{
	damageTimer = 0.f;
    player_AttackTimer = 0.5f;
    player_DamageTimer = 0.f;
}

void CombatSys::checkCombat(Player& player, Enemy& enemy, float deltaTime, bool playerAttacked)
{
    damageTimer += deltaTime;

    if (player.get_shape().findIntersection(enemy.get_e_Shape()))
    {
        if (damageTimer >= 3.0f && !player.getIsInvincible())
        {
            player.takeDamage(enemy.getDamage());
            damageTimer = 0.f;
        }
    }

    player_AttackTimer += deltaTime;

    if (playerAttacked)
    {
        if (player.get_shape().findIntersection(enemy.get_e_Shape()))
        {
            if (!enemy.e_GetIsInvincible())
            {
                enemy.takeDamage(player.getDamage());
            }
        }
    }
}

