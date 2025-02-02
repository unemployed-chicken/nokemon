#pragma once
#include "consoleUtil.h"
#include "globalVars.h"
#include "trainer.h"

Trainer generateTrainer(bool isUser = false);
Monster promptUserPreferedMonster();
void displyBattleField(Monster playersMonster, Monster aisMonster);
void displayActiveMonster(Monster m);