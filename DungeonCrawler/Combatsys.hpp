#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class CombatSys
{
public:
	CombatSys();
	void checkCombat(Player& player, Enemy& enemy, float deltaTime, bool playerAttacked);


private:
	float damageTimer;
	float player_DamageTimer;
	float player_AttackTimer;

};