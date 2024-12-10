#include "battle.h"

Trainer Battle::startBattle() {
	// battle logic begins here
	return Player;
}



int Battle::calculateDamage(double atk, double def, double movePower, double atkTypeMultiplier, double defTypeMultiplier, int crit, double random, int level) {
	// Roughly based on Gen 3 logic: https://bulbapedia.bulbagarden.net/wiki/Damage
	double damage = (((2 * level / 5 + 2) * movePower * (atk / def) / 50) + 2) * crit * atkTypeMultiplier * defTypeMultiplier * random; 
	return std::ceil(damage);
}