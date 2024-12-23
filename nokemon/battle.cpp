#include "battle.h"
#include "consoleUtil.h"
#include "helper.h"
#include <Windows.h>
#include "globalVars.h"
using std::tuple;
using std::make_tuple;
using std::get;

/* To add:
*    Perform a check to make sure Opponents fainted monsters are for sure fainted.
*    Switch out Logic
*    Make the battle display pause more intuitively
*
*/

/*
* Nice to Haves:
*    Change up print to console to receive a string for the sentence and a string for the object to insert
*    Display only moves that exist, rather than all move slots
*    Create more Nokemon and adjust stats to not be generic
*    Create More Moves
*    Fix display to prevent a Nokemon's HP from going negative (aka: if hp - x < 0, set to 0)
*/


Trainer Battle::startBattle() {
	printToConsole("Let the battle begin!");

	while (playerIsActive && AiIsActive) {
		// ---- validates both parties have an active monster on the battle field ----
		if (activeMonsterEmpty(PlayerActiveMonster) || (*PlayerActiveMonster).getCurrentHp() <= 0) { // This will start as null pointer?
			setFirstActiveMonster();
			std::cout << "Go " << (*PlayerActiveMonster).getName() << "!\n";
		}

		if (activeMonsterEmpty(AIActiveMonster) || (*AIActiveMonster).getCurrentHp() <= 0) { // This will start as null pointer?
			Monster* m = getAiActiveMonster();
			setAIActiveMonster(m);
			std::cout << "Your opponent chose " << (*AIActiveMonster).getName() << ".\n";
			printToConsole("FIGHT!!!!\n");
		}

		// ---- display battle field before player move choice ----
		displyBattleField( (*PlayerActiveMonster), (*AIActiveMonster));

		Move& playerMoveChoice = getPlayersMove();
		Move& aiMoveChoice = getAiMove();

		tuple <Monster&, Move&> playerMove((*PlayerActiveMonster), playerMoveChoice); // Does this need to store a pointer 
		tuple <Monster&, Move&> aiMove( (*AIActiveMonster), aiMoveChoice); // Does this need to store a pointer
		 
		// ---- Begin attack phase ----
		if ( (*PlayerActiveMonster).getSpd() >=  (*AIActiveMonster).getSpd()) {
			attackPhase(playerMove, aiMove);
		}
		else {
			attackPhase(aiMove, playerMove);
		}

		// ---- Assess Monster Status ----
		if (!(*PlayerActiveMonster).hasHealth()) {
			std::cout << (*PlayerActiveMonster).getName() << " has fainted!\n";
			(*Player).incrementInactivePartyCount();
			playerIsActive = (*Player).isTrainerActive();
		}

		if (!(*AIActiveMonster).hasHealth()) {
			std::cout << (*AIActiveMonster).getName() << " has fainted!\n";
			(*AI).incrementInactivePartyCount();
			AiIsActive = (*AI).isTrainerActive();
		}
	}

	if (playerIsActive) {
		return (*Player);
	}
	return (*AI);
}



int Battle::calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level) {
	// Roughly based on Gen 3 logic: https://bulbapedia.bulbagarden.net/wiki/Damage
	double damage = (((2 * level / 5 + 2) * movePower * (atk / def) / 50) + 2) * crit * atkTypeMultiplier * defTypeMultiplier * random; 
	return std::ceil(damage);
}

void Battle::setFirstActiveMonster() {
	while (true) {
		Monster* m = getPlayerActiveMonster(); // What happens if this returns null
		if (m) { // This will probably need to change
			return setPlayerActiveMonster(m); 
		} 
		printToConsole("You must select a Nokemon to start the battle.");
	}
}

Monster* Battle::getPlayerActiveMonster() { 
	printSpacerS();
	while (true) {
		printToConsole("Choose a Nokemon to battle!");
		int chosenNokemon = (*Player).requestNokemonIndexNumber();
		if (chosenNokemon == -1) {
			return nullptr;
		}
		
		--chosenNokemon;
		if (chosenNokemon >= 0 && chosenNokemon < (*Player).getPartyCount()) {
			Monster* chosen = &(*Player).getMonster(chosenNokemon);
			if ((*chosen).getCurrentHp() > 0) {
				return chosen;
			}
			printToConsole("The chosen Nokemon is fainted. Please choose another.");
		}
		else {
			printToConsole("You do not have a Nokemon in that slot. Please pick again.");
		}
	}
}

Monster* Battle::getAiActiveMonster() {
	srand(time(0));
	int i = rand() % (*AI).getPartyCount();
	return &(*AI).getMonster(i);
}

void Battle::setPlayerActiveMonster(Monster* m) {
	PlayerActiveMonster = m;
}

void Battle::setAIActiveMonster(Monster* m) {
	AIActiveMonster = m;
}

void Battle::attackPhase(std::tuple<Monster&, Move&> first, std::tuple<Monster&, Move&> second) { // Does this need to pass a pointer monster?
	// First monster move
	monsterAttack(first, get<0>(second));
	
	// Second Monster move
	if (get<0>(second).hasHealth()) {
		monsterAttack(second, get<0>(first));
	}
}

void Battle::monsterAttack(std::tuple<Monster&, Move&> attacker, Monster& defender) {
	printSpacerL();
	std::cout << get<0>(attacker).getName() << " used " << get<1>(attacker).getName() << ". \n";
	Sleep(500);
	printSpacerS();

	if (!calculateIsHit(attacker, defender)) {
		attackMiss(get<1>(attacker));
	} 
	else if (get<1>(attacker).getAtkType() == get<1>(attacker).attackTypeStringToEnum("Special")) {
		attackSpecial(attacker, defender);
	}
	else {
		attackPhysical(attacker, defender);
	}
	Sleep(2000);
}

void Battle::attackSpecial(std::tuple<Monster&, Move&> attacker, Monster& defender) {
	Monster& atkM = get<0>(attacker);
	Move& attack = get<1>(attacker);
	double critVal = calculateCritValue();
	int damage = calculateDamage(
		atkM.getSpAtk(), defender.getSpDef(), attack.getPower(), calculateAtkTypeMultiplier(atkM, attack), 
		calculateDefTypeMultiplier(defender, attack), critVal, calculateRandomDamageModifier()
	);

	// Below To Be Removed
	printSpacerS();
	std::cout << "Damage Calculated is: " << damage << '\n';
	printSpacerS();
	// Above to be Removed
	// 

	defender.takeDamage(damage);
	if (attack.getName() != "Struggle") { // Should never touch this as Struggle is never Special. But leave just in case of wacky game mechanics like a special ability flips special and phys
		attack.decrementUsesByOne();
	}
}


void Battle::attackPhysical(std::tuple<Monster&, Move&> attacker, Monster& defender) {
	Monster& atkM = get<0>(attacker);
	Move& attack = get<1>(attacker);
	double critVal = calculateCritValue();
	int damage = calculateDamage(
		atkM.getAtk(), defender.getDef(), attack.getPower(), calculateAtkTypeMultiplier(atkM, attack),
		calculateDefTypeMultiplier(defender, attack), critVal, calculateRandomDamageModifier()
	);

	// Below To Be Removed
	printSpacerS();
	std::cout << "Damage Calculated is: " << damage << '\n';
	printSpacerS();
	// Above to be Removed
	// 

	defender.takeDamage(damage);
	if (attack.getName() != "Struggle") {
		attack.decrementUsesByOne();
	}
}


void Battle::attackMiss(Move& attack) {
	printToConsole("THE ATTACK MISSED!");
	attack.decrementUsesByOne();
}


double Battle::calculateCritValue() {
	int random = rand();
	
	if ((random % 10) == 9) {
		printToConsole("Critical hit!");
		return 2.0;
	}
	return 1.0;
}

double Battle::calculateRandomDamageModifier() {
	int random = rand() % 16;
	return (random + 85.0) / 100.0;
}

bool Battle::calculateIsHit(std::tuple<Monster&, Move&> attacker, Monster& defender) {
	double moveAccuracy = get<1>(attacker).getAccuracy();
	if (moveAccuracy > 100) {
		return true;
	}
	int accuracyRoll = rand() % 101;
	double attackAccuracyScore = (moveAccuracy * get<0>(attacker).getAcc()) / (defender.getEvn() + 100);

	printSpacerL();
	std::cout << "Attack accuracy score: " << attackAccuracyScore << " || Accuracy roll is " << accuracyRoll << '\n';
	printSpacerL();

	return attackAccuracyScore >= accuracyRoll;
}


double Battle::calculateAtkTypeMultiplier(Monster attacker, Move attack) {
	if (attacker.getMonsterType().getObjectType() == attack.getMoveType().getObjectType()) {
		return 1.5;
	}
	else if (attack.getMoveType().getMultiplier(attacker.getMonsterType().getObjectType()) > 1) {
		return .5;
	}
	return 1.0;
}

double Battle::calculateDefTypeMultiplier(Monster defender, Move attack) {
	double x = attack.getMoveType().getMultiplier(defender.getMonsterType().getObjectType());
	if (x < 1) {
		printToConsole("The attack wasn't very effective...");
	}
	else if (x == 1) {
		printToConsole("The attack was neutral effective.");
	}
	else if (x > 1) {
		printToConsole("The attack was super effective!");
	}
	else {
		printToConsole("Something went wrong calculating the defType Multiplier.");
	}
	return x;
}

Move& Battle::getPlayersMove() {
	while (true) {
		if (!(*PlayerActiveMonster).hasActiveMoves()) {
			std::cout <<  (*PlayerActiveMonster).getName() << " is all out of moves. Using Struggle." << '\n';
			return AllMoves.at("struggle");
		}

		 (*PlayerActiveMonster).printMovesForBattle();
		printToConsole("What move should your Nokemon use? ");
		int slot = promptUserInputInt("Select the number associated the move you would like to use.");
		Move& mv =  (*PlayerActiveMonster).getMoveFromSlot(slot);
		if (mv.moveNotEmpty() && mv.hasUsagesLeft()) {
			return mv;
		}
		else if (!mv.moveNotEmpty()) {
			printToConsole("Your monster doesn't have a move assigned to that slot.");
		}
		else if (!mv.hasUsagesLeft()) {
			std::cout <<  (*PlayerActiveMonster).getName() << " has no moves left for " << mv.getName() << ".\n";
		}
	}
}

Move& Battle::getAiMove() {
	// Checks monster for Active Moves
	if (!(*AIActiveMonster).hasActiveMoves()) {
		return AllMoves.at("struggle");
	}

	srand(time(0));
	int x = 4;
	while (x > 0) {
		int slot = (rand() % x) + 1;
		Move& mv =  (*AIActiveMonster).getMoveFromSlot(slot);
		if (mv.moveNotEmpty() && mv.hasUsagesLeft()) {
			return mv;
		}
		else if (!mv.moveNotEmpty()) {
			--x;
		}
	}
}

bool Battle::activeMonsterEmpty(Monster* m) {
	if (m) {
		return false;
	} 
	return true;
}