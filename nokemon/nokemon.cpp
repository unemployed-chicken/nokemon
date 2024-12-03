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
		p1.setMonster(promptUserPreferedMonster());
		p2.setMonster(getRandomMonster());
	}

	p1.displayParty();
	printSpacerL();
	p2.displayParty();

	std::cout << "done" << std::endl;
}


