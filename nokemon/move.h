#pragma once
#include <iostream>
#include <map>
#include "type.h"
#include "simdjson.h"

/*
* For the purposes of this application, I would prefer precision of math over the benefits of saving space.
* I should not be dealing with large enough data sets where I must worry about optimization.
* A good project in the future may be to convert to floats and see what the performance looks like and see
* if there are any major math bugs.
*/ 
//extern std::map<std::string, Type> AllTypes;


class Move {
	std::string Name;
	Type MoveType;
	double Power;
	double Accuracy;
	double MaxUses;
	double Uses;
	double HitCount;

public:
	Move(std::string name, Type movetype, double power, double accuracy, double maxuses, double hitcount = 1) {
		Name = name;
		MoveType = movetype;
		Power = power;
		Accuracy = accuracy;
		HitCount = hitcount;
		MaxUses = maxuses;
		Uses = maxuses;
	};

	 Move(simdjson::ondemand::object moveObject, std::map<std::string, Type> AllTypes) {
		std::string_view stringViewName = moveObject.find_field("name").get_string();
		Name = std::string(stringViewName);
		
		std::string_view stringViewMoveType = moveObject.find_field("type").get_string();
		MoveType = AllTypes.at(std::string(stringViewMoveType));

		Power = double(moveObject.find_field("power"));
		Accuracy = double(moveObject.find_field("accuracy"));
		double totalUses = double(moveObject.find_field("maxUses"));
		MaxUses = totalUses;
		Uses = totalUses;
		HitCount = double(moveObject.find_field("hitCount"));
	};

	Move() {
		Name = "Empty";
		Power = 0.0;
		Accuracy = 0.0;
		HitCount = 0;
		MaxUses = 0;
		Uses = MaxUses;
	};

	std::string getName() const;
	double getMaxUses() const;
	Type getMoveType() const;
	double getPower() const;
	double getAccuracy() const;
	double getHitCount() const;
	double getUses() const;
	void decrementUsesByOne();
	void displayMove();

};
