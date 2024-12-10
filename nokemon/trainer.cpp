#include "trainer.h"
#include "consoleUtil.h"
#include <vector>
using std::string;


// Getters and Setters
string Trainer::getName() const { return Name; }
Monster& Trainer::getMonster(int i) { return Monsters.at(i); }
int Trainer::getPartyCount() const { return Monsters.size(); }

void Trainer::setMonster(Monster& m, const int nokemonSlot) {
	if (nokemonSlot < 0) {
		return;
	}
	else if (Monsters.size() >= 6 && nokemonSlot == 0) {
		int indexToReplace = getIndexToReplace(m);
		return setMonster(m, indexToReplace);
	}
	else if (Monsters.size() >= 6) {
		int i = nokemonSlot - 1;
		Monsters.erase(Monsters.begin() + i);
		Monsters.insert(Monsters.begin() + i, m);
	}
	else {
		Monsters.push_back(m);
	}
}

int Trainer::getIndexToReplace(const Monster& m) {
	while (true) {
		printSpacerL();
		std::cout << "Your party is full. Please choose which Nokemon you would like to replace with " << m.getName() << ".\n";
		int chosenIndex = requestNokemonIndexNumber();
		printSpacerL();
		return chosenIndex;
	}
}

void Trainer::displayParty() {
	for (int i = 0; i < Monsters.size(); ++i) {
		int spot = i + 1;
		std::cout << spot << ": " << Monsters[i].getName() << '\n';
	}
}

int Trainer::requestNokemonIndexNumber() {
	displayParty();
	return promptUserInputInt("Type the number next to the pokemon you would like to select. Type -1 to cancel.");
}
