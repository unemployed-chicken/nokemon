#include <iostream>
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

const int partySize = 3;

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

	p1.displayParty();
	printSpacerL();
	p2.displayParty();

	printSpacerL();
	p1.getMonster(0).attack(p2.getMonster(0), 5);

	printSpacerL();
	std::cout << "Current HP: " << p2.getMonster(0).getCurrentHp() << "\nMax HP: " << p2.getMonster(0).getMaxHp() << '\n';
	std::cout << "done" << std::endl;
}
