#pragma once
#include <iostream>
#include <vector>
#include "monster.h"

class Trainer {
	std::string Name;
	std::vector<Monster> Monsters;


public:
	Trainer(std::string name) {
		Name = name;
	}

	// Getters and Setters
	std::string getName() const;
	int getPartyCount() const;
	Monster getMonster(int i) const;
	void setMonster(Monster m, const int order = 0);
	int getIndexToReplace(const Monster& m);
	void displayParty();
	int requestNokemonIndexNumber();
};
