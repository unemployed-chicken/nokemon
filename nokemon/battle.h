#pragma once
#include "move.h"
#include "type.h"
#include "trainer.h"

enum BattleOption {
	FIGHT,
	SWAP
};


class Battle {
	Trainer* Player;
	Trainer* AI;
	Monster* PlayerActiveMonster;
	Monster* AIActiveMonster;
	bool playerIsActive = true;
	bool AiIsActive = true;

	int calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level = 10);
	void setPlayerActiveMonster(Monster* m);
	void setAIActiveMonster(Monster* m);
	Monster* playerChooseMonster();
	Monster* getAiActiveMonster();
	Move* getPlayersMove();
	Move* getAiMove();
	void attackPhase(std::tuple<Monster&, Move*> first, std::tuple<Monster&, Move*> second);
	void monsterAttack(std::tuple<Monster&, Move*> attacker, Monster& defender);
	void attackSpecial(std::tuple<Monster&, Move*> attacker, Monster& defender);
	void attackPhysical(std::tuple<Monster&, Move*> attacker, Monster& defender);
	void attackMiss(Move& attack);
	double calculateCritValue();
	double calculateRandomDamageModifier();
	double calculateAtkTypeMultiplier(Monster attacker, Move attack);
	double calculateDefTypeMultiplier(Monster defender, Move attack);
	bool calculateIsHit(std::tuple<Monster&, Move*> attacker, Monster& defender);
	bool monsterEmpty(Monster* m);
	bool moveEmpty(Move* m);
	BattleOption playerTurnChoice();
	void displayPlayerTurnOptions();
	Monster* playerSelectsMonsterToSwap();
	bool selectedMonsterAlreadyActive(Monster* m);
	void playerChoosesMonsterToBattle();
	Move* playerChoosesBattleAction();
	void displayDamageTaken(double damage, Monster defender);
	void displayFainted(Monster* m, Trainer* t);

public:
	Battle(Trainer& player, Trainer& ai) {
		Player = &player;
		AI = &ai;
	}

	Trainer startBattle();
};
