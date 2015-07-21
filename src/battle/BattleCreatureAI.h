//
// Created by TriD on 19.07.2015.
//

#ifndef FAMILY_BUSINESS_BATTLECREATUREAI_H
#define FAMILY_BUSINESS_BATTLECREATUREAI_H


#include <vector>

#include "BattleCreature.h"

using BattleCreatureParty = std::vector<BattleCreaturePtr>;

class BattleCreatureAI : public BattleCreature {
private:
    const BattleCreatureParty &enemyParty;
    std::shared_ptr<BattleCreature> target;
public:
    BattleCreatureAI(const CreaturePtr &creature, const BattleCreatureParty &enemies) : BattleCreature(creature),
                                                                                        enemyParty(enemies) { }
    const std::shared_ptr<BattleCreature> &getTarget() const { return target; }
    void setTarget(const std::shared_ptr<BattleCreature> &target) { BattleCreatureAI::target = target; }

    void updateTarget();
};


#endif //FAMILY_BUSINESS_BATTLECREATUREAI_H
