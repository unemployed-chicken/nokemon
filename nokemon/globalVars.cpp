#include "globalVars.h"

std::map<std::string, Type> AllTypes = {};
std::map<std::string, Move> AllMoves = {};
std::map<std::string, Monster> AllMonsters = {};
simdjson::ondemand::parser parser;

void generateAllTypesMovesMonsters() {
	// generate all types
	simdjson::padded_string json = simdjson::padded_string::load("all_types.json");
	simdjson::ondemand::document jsonDoc = parser.iterate(json);
	simdjson::ondemand::object object = jsonDoc.get_object();
	generateAllTypes(object);

	// generate all moves
	json = simdjson::padded_string::load("all_moves.json");
	jsonDoc = parser.iterate(json);
	object = jsonDoc.get_object();
	generateAllMoves(object);

	// generate all monsters
	json = simdjson::padded_string::load("all_nokemon.json");
	jsonDoc = parser.iterate(json);
	object = jsonDoc.get_object();
	generateAllMonsters(object);
}

void generateAllTypes(simdjson::ondemand::object object) {
	for (auto field : object) {
		std::string_view typeName = field.unescaped_key();
		simdjson::ondemand::object multipliers = field.value().find_field("multipliers");
		AllTypes[std::string(typeName)] = Type(typeName, multipliers);
	};
}

void generateAllMoves(simdjson::ondemand::object object) {
	for (auto field : object) {
		std::string_view moveName = field.unescaped_key();
		simdjson::ondemand::object moveValues = field.value();
		Move m = Move(moveValues, AllTypes);

		AllMoves[std::string(moveName)] = m;
	}
}

void generateAllMonsters(simdjson::ondemand::object object) {
	for (auto field : object) {
		std::string_view monsterIdentifier = field.unescaped_key();
		simdjson::ondemand::object monsterValues = field.value();
		Monster m = Monster(std::string(monsterIdentifier), monsterValues);
		AllMonsters[std::string(monsterIdentifier)] = m;
	}
}

void displayAllMoves() {
	for (auto itr = AllMoves.begin(); itr != AllMoves.end(); ++itr) {
		(*itr).second.displayMoveDetailed();
	}
}

void displayAllMonsters() {
	for (auto itr = AllMonsters.begin(); itr != AllMonsters.end(); ++itr) {
		(*itr).second.printMonsterBrief();
	}
}

void displayAllMonstersWithMoves() {
	for (auto itr = AllMonsters.begin(); itr != AllMonsters.end(); ++itr) {
		(*itr).second.printMonster();
		(*itr).second.printMovesDetailed();
	}
}