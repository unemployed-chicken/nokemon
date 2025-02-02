#pragma once
#include <iostream>
#include <vector>
#include "monster.h"

class Trainer {
	std::string Name;
	std::vector<Monster> Party;
	int InactivePartyCount=0;

public:
	Trainer(std::string name) {
		Name = name;
	}

	Trainer() {
		Name = "none";
	}

	// Getters and Setters
	std::string getName() const;
	int getPartyCount() const;
	Monster& getMonster(int i);
	void setMonster(Monster& m, const int order = 0);
	int getIndexToReplace(const Monster& m);
	void displayParty();
	int requestNokemonIndexNumber();
	int getInactivePartyCount() const;
	void incrementInactivePartyCount();
	bool isTrainerActive();

	// For testing purposes
	void setName(std::string name);
};
