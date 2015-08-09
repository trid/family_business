//
// Created by TriD on 27.06.2015.
//

#include "BattleCreature.h"

BattleCreature::BattleCreature(int id, int creature) : creatureId(creature), steps(getCreatureById(creature).getSpeed()),
                                                       currentHp(getCreatureById(creature).getHitPoints()), id(id) {

}

void BattleCreature::takeDamage(int damage) {
    int noDefenceDamage = damage - getCreatureById(creatureId).getDefence();
    int realDamage = noDefenceDamage > 0 ? noDefenceDamage : 0;
    currentHp > realDamage ? currentHp -= realDamage: currentHp = 0;
}
