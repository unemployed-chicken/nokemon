#include "helper.h"
using std::string;

Trainer generateTrainer(bool isUser) {
	if (isUser) {
		return Trainer(promptUserInputString("What is your name"));
	}
	return Trainer("Opponent");
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
				Monster m = (*itr).second;
				std::cout << "You chose " << m.getName() << '\n';
				pause(1000);
				return m;
			}
			printToConsole("That is not a valid Nokemon. The name is case sensitive. Type 'all' to get a list of Nokemon");
			pause(1000);
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
		}
		++i;
	}
}

void displyBattleField(Monster playersMonster, Monster aisMonster) {
	printSpacerGap(6);
	printSpacerL();
	std::cout << "Opponent's Monster\n";
	displayActiveMonster(aisMonster);
	printSpacerGap(2);
	std::cout << "Your Monster\n";
	displayActiveMonster(playersMonster);
	printSpacerL();
}


void displayActiveMonster(Monster m) {
	std::cout << m.getName() << "\t\t\tHP: " << m.getCurrentHp() << "/" << m.getMaxHp() << '\n';
}