#include "battle.h"
#include "consoleUtil.h"
#include "helper.h"
using std::tuple;
using std::make_tuple;
using std::get;

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

		tuple <Monster&, Move> playerMove(PlayerActiveMonster, getPlayersMove());
		tuple <Monster&, Move> aiMove(PlayerActiveMonster, getAiMove());
		 
		// Begin attack phase
		if (PlayerActiveMonster.getSpd() >= AIActiveMonster.getSpd()) {
			
			attackPhase(playerMove, aiMove);
		}
		else {
			attackPhase(aiMove, playerMove);
		}

		printSpacerL();
		std::cout << "Your move: " << get<1>(playerMove).getName() << '\n';
		std::cout << "Your opponent's move: " << get<1>(aiMove).getName() << '\n';
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

void Battle::attackPhase(std::tuple<Monster&, Move> first, std::tuple<Monster&, Move> second) {
	// First monster move
	monsterAttack(first, get<0>(second));
	// Second Monster move
	if (get<0>(second).hasHealth()) {
		monsterAttack(second, get<0>(first));
	}
}

void Battle::monsterAttack(std::tuple<Monster&, Move> attacker, Monster& defender) {
	if (get<1>(attacker).getAtkType() == get<1>(attacker).attackTypeStringToEnum("Special")) {
		attackSpecial(attacker, defender);
	}
	else {
		attackPhysical(attacker, defender);
	}
}

void Battle::attackSpecial(std::tuple<Monster&, Move> attacker, Monster& defender) {
	Monster atkM = get<0>(attacker);
	Move attack = get<1>(attacker);
	int damage = calculateDamage(
		atkM.getSpAtk(), defender.getSpDef(), attack.getPower(), calculateAtkTypeMultiplier(atkM, attack), 
		calculateDefTypeMultiplier(defender, attack), calculateCritValue(), calculateRandomDamageModifier()
	);

	// Below To Be Removed
	printSpacerS();
	std::cout << "Damage Calculated is: " << damage << '\n';
	printSpacerS();
	// Above to be Removed
	// 
	// do something with damage
}


void Battle::attackPhysical(std::tuple<Monster&, Move> attacker, Monster& defender) {
	Monster atkM = get<0>(attacker);
	Move attack = get<1>(attacker);
	int damage = calculateDamage(
		atkM.getAtk(), defender.getDef(), attack.getPower(), calculateAtkTypeMultiplier(atkM, attack),
		calculateDefTypeMultiplier(defender, attack), calculateCritValue(), calculateRandomDamageModifier()
	);

	// Below To Be Removed
	printSpacerS();
	std::cout << "Damage Calculated is: " << damage << '\n';
	printSpacerS();
	// Above to be Removed
	// 
	// do something with damage
}


double Battle::calculateCritValue() {
	printSpacerS();
	int random = rand();
	std::cout << "Critical Random Value was: " << random << '\n';
	
	double x = random % 10;
	std::cout << "Critical value should be between 0 and 9: " << x << '\n';
	
	if (x == 9) {
		printToConsole("It was a critical hit!");
		return 2.0;
	}

	// Below To Be Removed
	std::cout << "Crit value is 1" << '\n';
	printSpacerS();
	// Above to be Removed
	return 1.0;
}

double Battle::calculateRandomDamageModifier() {
	printSpacerS();
	int random = rand() % 16;
	std::cout << "RandomDamage Modulo Random Value was: " << random << '\n';

	double x =  (random + 85.0) / 100.0;

	// Below To Be Removed
	printSpacerS();
	std::cout << "Random value should be between .85 and 1.0: " << x << '\n';
	printSpacerS();
	// Above to be Removed

	return x;
}


double Battle::calculateAtkTypeMultiplier(Monster attacker, Move attack) {
	if (attacker.getMonsterType().getObjectType() == attack.getMoveType().getObjectType()) {
		printSpacerS();
		std::cout << "The Attacking Monster is using a powerful move!" << '\n';
		printSpacerS();
		return 1.5;
	}
	else if (attack.getMoveType().getMultiplier(attacker.getMonsterType().getObjectType()) > 1) {
		printSpacerS();
		std::cout << "The Attacking Monster is using a weak move..." << '\n';
		printSpacerS();
		return .5;
	}
	printSpacerS();
	std::cout << "The Attacking Monster is using a neutral move." << '\n';
	printSpacerS();
	return 1.0;
}

double Battle::calculateDefTypeMultiplier(Monster defender, Move attack) {
	double x = attack.getMoveType().getMultiplier(defender.getMonsterType().getObjectType());
	if (x < 1) {
		printSpacerS();
		std::cout << "The attack wasn't very effective..." << '\n';
		printSpacerS();
	}
	else if (x == 1) {
		printSpacerS();
		std::cout << "The attack was neutral effective." << '\n';
		printSpacerS();
	}
	else if (x > 1) {
		printSpacerS();
		std::cout << "The attack was super effective!" << '\n';
		printSpacerS();
	}
	else {
		printSpacerS();
		std::cout << "Something went wrong calculating the defType Multiplier." << '\n';
		printSpacerS();
	}
	return x;
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
