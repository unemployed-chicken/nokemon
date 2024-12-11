#include "battle.h"
#include "consoleUtil.h"

Trainer Battle::startBattle() {
	printToConsole("Let the battle begin!");
	bool playerIsActive = true;
	bool AiIsActive = true;

	while (playerIsActive && AiIsActive) {
		if (PlayerActiveMonster.getName() == "NONE") {
			setFirstActiveMonster();
		}

		if (AIActiveMonster.getName() == "NONE") {
			Monster m = getAiActiveMonster();
			setAIActiveMonster(m);
		}

		printSpacerL();
		std::cout << "You are battling with " << PlayerActiveMonster.getName() << '\n';
		std::cout << "Your opponent chose: " << AIActiveMonster.getName() << '\n';
		break;
	}
	return Player;
}



int Battle::calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level) {
	// Roughly based on Gen 3 logic: https://bulbapedia.bulbagarden.net/wiki/Damage
	double damage = (((2 * level / 5 + 2) * movePower * (atk / def) / 50) + 2) * crit * atkTypeMultiplier * defTypeMultiplier * random; 
	return std::ceil(damage);
}

bool Battle::isTrainerActive(Trainer t) {
	return t.getInactivePartyCount() < t.getPartyCount();
}

void Battle::setFirstActiveMonster() {
	while (true) {
		Monster m = getPlayerActiveMonster();
		if (m.getName() != "NONE") {
			return setPlayerActiveMonster(m);
		} 

		printToConsole("You must select a Nokemon to start the battle.");
	}
}

Monster Battle::getPlayerActiveMonster() {
	printSpacerS();
	while (true) {
		printToConsole("Choose a Nokemon to battle!");
		int chosenNokemon = Player.requestNokemonIndexNumber();
		if (chosenNokemon == -1) {
			return Monster();
		}
		
		--chosenNokemon;
		if (chosenNokemon >= 0 && chosenNokemon < Player.getPartyCount()) {
			Monster chosen = Player.getMonster(chosenNokemon);
			if (chosen.getCurrentHp() > 0) {
				return chosen;
			}
			printToConsole("The chosen Nokemon is fainted. Please choose another.");
		}
		else {
			printToConsole("You do not have a Nokemon in that slot. Please pick again.");
		}
	}
}

Monster Battle::getAiActiveMonster() {
	srand(time(0));
	int i = rand() % AI.getPartyCount();
	return AI.getMonster(i);
}

void Battle::setPlayerActiveMonster(Monster& m) {
	PlayerActiveMonster = m;
}

void Battle::setAIActiveMonster(Monster& m) {
	AIActiveMonster = m;
}