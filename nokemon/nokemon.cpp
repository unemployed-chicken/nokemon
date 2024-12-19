#include <iostream>
#include "battle.h"
#include "consoleUtil.h"
#include "globalVars.h"
#include "helper.h"
#include "move.h"
#include "simdjson.h"
#include "trainer.h"
#include "type.h"

/*
* Look into setting AllTypes, AllMoves, AllMonsters as a constexpr < This wont work
* for my implementation
*/

const int partySize = 2;

int main() {
	generateAllTypesMovesMonsters();

	printToConsole("Welcome to the world of Not Pokemon, or Nokemon!");
	Trainer p1 = generateTrainer(true);
	Trainer p2 = generateTrainer();

	srand(time(0));

	for (int i = 0; i < partySize; ++i) {
		Monster p1Monster = promptUserPreferedMonster();
		p1.setMonster(p1Monster);
		Monster p2Monster = getRandomMonster();
		p2.setMonster(p2Monster);
	}

	Battle b = Battle(p1, p2);
	Trainer winner = b.startBattle();
	if (winner.getName() != p2.getName()) {
		printToConsole("CONGRATS! YOU WON!!!!!");
	}
	else {
		printToConsole("Sorry, You lost. Better luck next time. =(");
	}
	std::cout << "done" << std::endl;
}
