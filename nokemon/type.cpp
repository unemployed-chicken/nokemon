#include <iostream>
#include <map>
#include <vector>
#include "type.h"
#include "consoleUtil.h"
using std::string;
using std::map;
using std::vector;


string Type::getObjectType() const { return ObjectType; }
float Type::getMultiplier(string t) const {
	if (Multipliers.find(t) == Multipliers.end()) {
		return 1.0;
	}
	return Multipliers.at(t);
}

void Type::displayType() {
	printSpacerS();
	std::cout << ObjectType << '\n';
	for (auto itr = Multipliers.begin(); itr != Multipliers.end(); ++itr) {
		std::cout << "Type: " << (*itr).first << " | multiplier: " << (*itr).second << '\n';
	}
}