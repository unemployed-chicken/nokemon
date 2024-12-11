#pragma once
#include "type.h"
#include "trainer.h"

class Battle {
	Trainer Player;
	Trainer AI;
	Monster PlayerActiveMonster;
	Monster AIActiveMonster;

	int calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level = 10);
	bool isTrainerActive(Trainer t);
	void setFirstActiveMonster();
	void setPlayerActiveMonster(Monster& m);
	void setAIActiveMonster(Monster& m);
	Monster getPlayerActiveMonster();
	Monster getAiActiveMonster();

public:
	Battle(Trainer& player, Trainer& ai) {
		Player = player;
		AI = ai;
	}

	Trainer startBattle();
};



