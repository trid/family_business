//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLE_H
#define FAMILY_BUSINESS_BATTLE_H

#include "BattleCreature.h"
#include "BattleMap.h"

class Battle {
private:
    BattleMap battleMap;
    std::vector<BattleCreaturePtr> turns;
    std::vector<BattleCreaturePtr>::iterator current;

    BattleCreaturePtr character;
    BattleCreaturePtr monster;

    void updateTurns();
    void nextCreature();
public:
    Battle(CreaturePtr character, CreaturePtr monster);

    const BattleMap &getBattleMap() const { return battleMap; }
    void makeTurn();
    std::vector<BattleCreaturePtr>::iterator& getCurrent() { return current; }
};


#endif //FAMILY_BUSINESS_BATTLE_H
