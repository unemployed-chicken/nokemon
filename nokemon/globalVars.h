#pragma once
#include <iostream>
#include <map>
#include "simdjson.h"
#include "type.h"
#include "move.h"
#include "monster.h"

extern std::map<std::string, Type> AllTypes;
extern std::map<std::string, Move> AllMoves;
extern std::map<std::string, Monster> AllMonsters;

void generateAllTypesMovesMonsters();
void generateAllTypes(simdjson::ondemand::object object);
void generateAllMoves(simdjson::ondemand::object object);
void generateAllMonsters(simdjson::ondemand::object object);