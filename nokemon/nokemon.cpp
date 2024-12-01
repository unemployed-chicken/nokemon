#include <iostream>
#include "simdjson.h"
#include "move.h"
#include "type.h"

/*
* NEXT STEP: Figure out creating an External Variable
* Look into setting AllTypes, AllMoves, AllMonsters as a constexpr 
*/

int main() {
	std::map<std::string, Type> AllTypes = {};
	std::map<std::string, Move> AllMoves = {};

	simdjson::ondemand::parser parser;
	
	// Generate All Types
	simdjson::padded_string json = simdjson::padded_string::load("all_types.json");
	simdjson::ondemand::document jsonDoc = parser.iterate(json);
	simdjson::ondemand::object object = jsonDoc.get_object();
	for (auto field : object) {
		std::string_view typeName = field.unescaped_key();
		simdjson::ondemand::object multipliers = field.value().find_field("multipliers");
		AllTypes[std::string(typeName)] = Type(typeName, multipliers);
	}; 

	// Generate All Moves
	json = simdjson::padded_string::load("all_moves.json");
	jsonDoc = parser.iterate(json);
	object = jsonDoc.get_object();

	for (auto field : object) {
		std::string_view moveName = field.unescaped_key();
		simdjson::ondemand::object moveValues = field.value();
		Move m = Move(moveValues, AllTypes);
		m.displayMove();

		AllMoves[std::string(moveName)] = m;
	}

	std::cout << "------------------------------------------\n";
	std::cout << "------------------------------------------\n";
	std::cout << "------------------------------------------\n";
	for (auto itr = AllMoves.begin(); itr != AllMoves.end(); ++itr) {
		(*itr).second.displayMove();
	}

	std::cout << "done" << std::endl;
}

