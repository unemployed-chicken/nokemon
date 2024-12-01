#pragma once
#include <iostream>
#include <map>
#include <set>
#include "simdjson.h"



class Type {
	std::string ObjectType;
	std::map<std::string, double> Multipliers = {};

public:
	Type(std::string objectType, std::map<std::string, double> multipliers) {
		ObjectType = objectType;
		Multipliers = multipliers;
	};

	Type() {};

	Type(std::string_view typeName, simdjson::ondemand::object multipliers) {
		std::map<std::string, double> m = {};
		for (auto multiplier : multipliers) {
			std::string_view stringView = multiplier.unescaped_key();
			simdjson::ondemand::number numberValue = multiplier.value().get_number();

			m[std::string(stringView)] = double(numberValue);
		}

		ObjectType = std::string(typeName);
		Multipliers = m;
	};


	std::string getObjectType() const;
	float getMultiplier(std::string t) const;
	void displayType();
};