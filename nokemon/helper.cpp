#include "helper.h"
using std::string;

Trainer generateTrainer(bool isUser) {
	string name = "Opponent";
	if (isUser) {
		name = promptUserInputString("What is your name");
	}
	return Trainer(name);
}

Monster promptUserPreferedMonster() {
	while (true) {
		string userInput = promptUserInputString("Please type the name of the Nokemon you would like. (Type 'all' to get a list of all Nokemon)");
		if (userInput == "all" || userInput == "ALL" || userInput == "All") {
			printSpacerL();
			displayAllMonsters();
			printSpacerL();
		}
		else {
			auto itr = AllMonsters.find(userInput);
			if (itr != AllMonsters.end()) {
				return (*itr).second;
			}
			printToConsole("That is not a valid Nokemon. The name is case sensitive. Type 'all' to get a list of Nokemon");
		}
	}
}


Monster getRandomMonster() {
	srand(time(0));
	int index = rand() % AllMonsters.size();
	int i = 0;
	Monster m;
	for (auto itr = AllMonsters.begin(); itr != AllMonsters.end(); ++itr) {
		if (i == index) {
			return (*itr).second;
			//break;
		}
		++i;
	}
	//return m;
}

void displyBattleField(Monster playersMonster, Monster aisMonster) {
	printSpacerL();
	displayActiveMonster(aisMonster);
	printSpacerS();
	printSpacerS();
	displayActiveMonster(playersMonster);
	printSpacerL();
}


void displayActiveMonster(Monster m) {
	std::cout << m.getName() << "\t\t\tHP: " << m.getCurrentHp() << "/" << m.getMaxHp() << '\n';
}