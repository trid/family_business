//
// Created by TriD on 27.06.2015.
//

#include "BattleCreature.h"

using namespace BattleState;

BattleCreature::BattleCreature(int id, int creature) : creatureId(creature), steps(Main::getCreatureById(creature).getSpeed()),
                                                       currentHp(Main::getCreatureById(creature).getHitPoints()), id(id) {

}

void BattleCreature::takeDamage(int damage) {
    int defence = Main::getCreatureById(creatureId).getDefence();
    int noDefenceDamage = damage - defence;
    int realDamage = noDefenceDamage > 0 ? noDefenceDamage : 0;
    currentHp > realDamage ? currentHp -= realDamage: currentHp = 0;
}
