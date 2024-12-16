#include "battle.h"
#include "consoleUtil.h"
#include "helper.h"

Trainer Battle::startBattle() {
	printToConsole("Let the battle begin!");
	bool playerIsActive = true;
	bool AiIsActive = true;

	while (playerIsActive && AiIsActive) {
		// validates both parties have an active monster on the battle field.
		if (PlayerActiveMonster.getName() == "NONE") {
			setFirstActiveMonster();
		}

		if (AIActiveMonster.getName() == "NONE") {
			Monster m = getAiActiveMonster();
			setAIActiveMonster(m);
		}

		// display battle field before player move choice
		displyBattleField(PlayerActiveMonster, AIActiveMonster);

		Move playerMove = getPlayersMove();
		Move aiMove = getAiMove();

		printSpacerL();
		std::cout << "Your move: " << playerMove.getName() << '\n';
		std::cout << "Your opponent's move: " << aiMove.getName() << '\n';
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

Move Battle::getPlayersMove() {
	while (true) {
		if (!PlayerActiveMonster.hasActiveMoves()) {
			std::cout << PlayerActiveMonster.getName() << " is all out of moves. Using Struggle." << '\n';
			return Move(std::string("struggle"), AllTypes.at("normal"), 10.0, 101.0, 1.0);
		}

		PlayerActiveMonster.printMovesForBattle();
		printToConsole("What move should your Nokemon use? ");
		int slot = promptUserInputInt("Select the number associated the move you would like to use.");
		Move mv = PlayerActiveMonster.getMoveFromSlot(slot);
		if (mv.moveNotEmpty() && mv.hasUsagesLeft()) {
			return mv;
		}
		else if (!mv.moveNotEmpty()) {
			printToConsole("Your monster doesn't have a move assigned to that slot.");
		}
		else if (!mv.hasUsagesLeft()) {
			std::cout << PlayerActiveMonster.getName() << " has no moves left for " << mv.getName() << ".\n";
		}
	}
}

// There is an unidentified bug here. This crashed once during testing
// The bug may have been that I "rand() % 4" and not "rand() % x"
Move Battle::getAiMove() {
	srand(time(0));
	int x = 4;
	while (x > 0) {
		// Checks monster for Active Moves
		if (!AIActiveMonster.hasActiveMoves()) {
			return Move(std::string("struggle"), AllTypes.at("normal"), 10.0, 101.0, 1.0);
		}
		int slot = (rand() % x) + 1;
		Move mv = AIActiveMonster.getMoveFromSlot(slot);
		if (mv.moveNotEmpty() && mv.hasUsagesLeft()) {
			return mv;
		}
		else if (!mv.moveNotEmpty()) {
			--x;
		}
	}
}
