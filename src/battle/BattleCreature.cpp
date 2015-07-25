//
// Created by TriD on 27.06.2015.
//

#include "BattleCreature.h"

BattleCreature::BattleCreature(CreaturePtr creature) : creaturePtr(creature), steps(creature->getSpeed()),
                                                       currentHp(creature->getHitPoints()) {

}

void BattleCreature::takeDamage(int damage) {
    int noDefenceDamage = damage - creaturePtr->getDefence();
    int realDamage = noDefenceDamage > 0 ? noDefenceDamage : 0;
    currentHp > realDamage ? currentHp -= realDamage: currentHp = 0;
}
