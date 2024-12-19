#pragma once
#include "move.h"
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
	Move getPlayersMove();
	Move getAiMove();
	void attackPhase(std::tuple<Monster&, Move> first, std::tuple<Monster&, Move> second);
	void monsterAttack(std::tuple<Monster&, Move> attacker, Monster& defender);
	void attackSpecial(std::tuple<Monster&, Move> attacker, Monster& defender);
	void attackPhysical(std::tuple<Monster&, Move> attacker, Monster& defender);
	double calculateCritValue();
	double calculateRandomDamageModifier();
	double calculateAtkTypeMultiplier(Monster attacker, Move attack);
	double calculateDefTypeMultiplier(Monster defender, Move attack);

public:
	Battle(Trainer& player, Trainer& ai) {
		Player = player;
		AI = ai;
	}

	Trainer startBattle();
};



