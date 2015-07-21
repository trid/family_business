//
// Created by TriD on 19.07.2015.
//

#include <cstdlib>
#include "BattleCreatureAI.h"

void BattleCreatureAI::updateTarget() {
    BattleCreaturePtr closest = enemyParty[0];
    Point diff = closest->getPosition() - getPosition();
    int minDist = std::abs(diff.x + diff.y);

    for (auto creature: enemyParty) {
        if (creature->isDead()) {
            break;
        }

        diff = creature->getPosition() - getPosition();
        int dist = abs(diff.x + diff.y);
        if (minDist > dist) {
            dist = minDist;
            closest = creature;
        }
    }

    target = closest->isDead() ? nullptr : closest;
}
