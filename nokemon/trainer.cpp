#include "trainer.h"
#include "consoleUtil.h"
#include <vector>
using std::string;


// Getters and Setters
string Trainer::getName() const { return Name; }
Monster& Trainer::getMonster(int i) { return Party.at(i); }
int Trainer::getPartyCount() const { return Party.size(); }
int Trainer::getInactivePartyCount() const { return InactivePartyCount; }
void Trainer::incrementInactivePartyCount() { ++InactivePartyCount;  }

void Trainer::setMonster(Monster& m, const int nokemonSlot) {
	if (nokemonSlot < 0) {
		return;
	}
	else if (Party.size() >= 6 && nokemonSlot == 0) {
		int indexToReplace = getIndexToReplace(m);
		return setMonster(m, indexToReplace);
	}
	else if (Party.size() >= 6) {
		int i = nokemonSlot - 1;
		Party.erase(Party.begin() + i);
		Party.insert(Party.begin() + i, m);
	}
	else {
		Party.push_back(m);
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
	for (int i = 0; i < Party.size(); ++i) {
		int spot = i + 1;
		std::cout << spot << ") Name:" << Party[i].getName() << " | Type: " << Party[i].getMonsterType().getObjectType(); 
		std::cout << "| HP: " << Party[i].getCurrentHp() << "/" << Party[i].getMaxHp() << '\n';
	}
}

int Trainer::requestNokemonIndexNumber() {
	displayParty();
	return promptUserInputInt("Type the number next to the pokemon you would like to select. Type -1 to cancel.");
}

bool Trainer::isTrainerActive() {
	return InactivePartyCount < Party.size();
}
