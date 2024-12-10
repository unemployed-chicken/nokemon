#pragma once
#include <iostream>
#include <vector>
#include "move.h"
#include "type.h"
#include "globalVars.h"

extern std::map<std::string, Type> AllTypes;
extern std::map<std::string, Move> AllMoves;


class Monster {
    std::string Name;
    Type MonsterType;
    double MaxHp;
    double CurrentHp;
    double Atk;
    double Def;
    double SpAtk;
    double SpDef;
    double Spd;
    double Acc = 1;
    double Evn = 1;
    Move MoveSlot1;
    Move MoveSlot2;
    Move MoveSlot3;
    Move MoveSlot4;


public:
    Monster(std::string name, Type type, double hp, double atk, double def, double spAtk, double spDef, double spd) {
        Name = name;
        MonsterType = type;
        MaxHp = hp;
        CurrentHp = hp;
        Atk = atk;
        Def = def;
        SpAtk = spAtk;
        SpDef = spDef;
        Spd = spd;
    }

    Monster(std::string name, simdjson::ondemand::object monsterObject) {
        Name = name;

        std::string_view stringViewMoveType = monsterObject.find_field("type").get_string();
        MonsterType = AllTypes.at(std::string(stringViewMoveType));

        double hp = double(monsterObject.find_field("hp"));
        MaxHp = hp;
        CurrentHp = hp;
        Atk = double(monsterObject.find_field("atk"));
        Def = double(monsterObject.find_field("def"));
        SpAtk = double(monsterObject.find_field("spAtk"));
        SpDef = double(monsterObject.find_field("spDef"));
        Spd = double(monsterObject.find_field("spd"));

        int i = 0;
        for (std::string_view move : monsterObject["moves"]) {
            ++i;
            Move mv = AllMoves.at(std::string(move));
            setMoveSlot(i, mv);
        }
    }

    Monster() {
        Name = "NONE";
        MonsterType = Type();
        MaxHp = 0;
        CurrentHp = 0;
        Atk = 0;
        Def = 0;
        SpAtk = 0;
        SpDef = 0;
        Spd = 0;
    }

    void printMonster();
    void printMoves();

    // Getters and Setters
    Type getMonsterType() const;
    std::string getName() const;
    double getMaxHp() const;
    double getCurrentHp() const;
    void setCurrentHp(const double health);
    double getAtk() const;
    double getDef() const;
    double getSpAtk() const;
    double getSpDef() const;
    double getSpd() const;
    double getAcc() const;
    double getEvn() const;
    void setMoveSlot(int slot, const Move& move);
    void setAllMoveSlots(const Move& one, const Move& two);
    void setAllMoveSlots(const Move& one, const Move& two, const Move& three);
    void setAllMoveSlots(const Move& one, const Move& two, const Move& three, const Move& four);
    
    void attack(Monster& m, int damage);
};