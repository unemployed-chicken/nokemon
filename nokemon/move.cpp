#include "move.h"
#include "consoleUtil.h"

using std::string;
using std::map;


// Getters and Setters
string Move::getName() const { return Name; }
Type Move::getMoveType() const { return MoveType; }
double Move::getPower() const { return Power; }
double Move::getAccuracy() const { return Accuracy; }
double Move::getHitCount() const { return HitCount; }
double Move::getMaxUses() const { return MaxUses; }
double Move::getUses() const { return Uses; }
void Move::decrementUsesByOne() { Uses--; }

void Move::displayMove() {
	printSpacerS();
	std::cout << Name << ":\n\t";
	std::cout << "Type: " << MoveType.getObjectType() << "\n\t";
	std::cout << "Attack Type: " << attackTypeEnumToString(AtkType) << "\n\t";
	std::cout << "Power: " << Power << " | Accuracy: " << Accuracy << "\n\t";
	std::cout << "Move Counts: " << Uses << "/" << MaxUses << '\n';
	printSpacerS();
}

AttackType Move::attackTypeStringToEnum(string atkType) {
	if (atkType == "special" || atkType == "Special" || atkType == "SPECIAL") {
		return SPECIAL;
	}
	return PHYSICAL;
}

string Move::attackTypeEnumToString(AttackType atkType) {
	if (atkType == SPECIAL) {
		return "special";
	}
	return "physical";
}

