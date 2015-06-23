//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLE_H
#define FAMILY_BUSINESS_BATTLE_H


#include "BattleMap.h"

class Battle {
private:
    BattleMap battleMap;
public:
    Battle(CreaturePtr character, CreaturePtr monster): battleMap(character, monster) {}

    const BattleMap &getBattleMap() const { return battleMap; }
};


#endif //FAMILY_BUSINESS_BATTLE_H
