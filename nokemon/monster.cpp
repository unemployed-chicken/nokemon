#include <iostream>
#include "type.h"
#include "monster.h"
#include "consoleUtil.h"
using std::string;


void Monster::printMonster() {
    printSpacerS();
    std::cout << "{ Name: " << Name << ", Type: " << MonsterType.getObjectType() << ", Attack: " << Atk << ", Defense: " << Def << ", Special Attack: " << SpAtk;
    std::cout << ", Special Defense: " << SpDef << ", Speed: " << Spd << ", Accuracy: " << Acc << ", Evasion: " << Evn << " }\n";
}

void Monster::printMoves() {
    Move moves[] = { MoveSlot1, MoveSlot2, MoveSlot3, MoveSlot4 };
    for (int i = 0; i < 4; ++i) {
        std::cout << "Move " << i + 1 << ":\n";
        moves[i].displayMove();
        printSpacerS();
    }
}


Type Monster::getMonsterType() const { return MonsterType; }
string Monster::getName() const { return Name; }
double Monster::getMaxHp() const { return MaxHp; }
double Monster::getCurrentHp() const { return CurrentHp; }
void Monster::setCurrentHp(const double health) { CurrentHp = health; }
double Monster::getAtk() const { return Atk; }
double Monster::getDef() const { return Def; }
double Monster::getSpAtk() const { return SpAtk; }
double Monster::getSpDef() const { return SpDef; }
double Monster::getSpd() const { return Spd; }
double Monster::getAcc() const { return Acc; }
double Monster::getEvn() const { return Evn; }
void Monster::setMoveSlot(int slot, const Move& move) { // THIS NEEDS TO THROW AN ERROR IF SLOT IS NOT 1-4
    switch (slot) {
    case (1):
        MoveSlot1 = move;
        break;
    case (2):
        MoveSlot2 = move;
        break;
    case (3):
        MoveSlot3 = move;
        break;
    case (4):
        MoveSlot4 = move;
        break;
    default:
        std::cout << "THERE WAS AN ERROR ASSIGNING THE MOVE " << move.getName() << " TO " << Name << ".\n";
    }
}

void Monster::setAllMoveSlots(const Move& one, const Move& two) {
    MoveSlot1 = one;
    MoveSlot2 = two;
}

void Monster::setAllMoveSlots(const Move& one, const Move& two, const Move& three) {
    MoveSlot1 = one;
    MoveSlot2 = two;
    MoveSlot3 = three;
}

void Monster::setAllMoveSlots(const Move& one, const Move& two, const Move& three, const Move& four) {
    MoveSlot1 = one;
    MoveSlot2 = two;
    MoveSlot3 = three;
    MoveSlot4 = four;
}