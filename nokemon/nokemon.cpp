#include <iostream>
#include "simdjson.h"
#include "move.h"
#include "type.h"
#include "globalVars.h"

/*
* Look into setting AllTypes, AllMoves, AllMonsters as a constexpr < This wont work
* for my implementation
* 
* Next Steps: 
* - Create an array in all_nokemon for the moves of each nokemon
* - Incorporate the moves in the automatic generation of these nokemon
* 
*/

int main() {
	generateAllTypesMovesMonsters();

	for (auto itr = AllMoves.begin(); itr != AllMoves.end(); ++itr) {
		(*itr).second.displayMove();
	}

	std::cout << "-----------------------------------------------\n";

	for (auto itr = AllMonsters.begin(); itr != AllMonsters.end(); ++itr) {
		(*itr).second.printMonster();
	}

	std::cout << "done" << std::endl;
}

