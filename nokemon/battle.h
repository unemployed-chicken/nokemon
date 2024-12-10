#pragma once
#include "type.h"
#include "trainer.h"

class Battle {
	Trainer Player;
	Trainer AI;

	int calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level = 10);

public:
	Battle(Trainer& player, Trainer& ai) {
		Player = player;
		AI = ai;
	}

	Trainer startBattle();
};

