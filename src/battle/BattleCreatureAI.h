//
// Created by TriD on 19.07.2015.
//

#ifndef FAMILY_BUSINESS_BATTLECREATUREAI_H
#define FAMILY_BUSINESS_BATTLECREATUREAI_H


#include <vector>

#include "BattleCreature.h"

namespace BattleState {

    using BattleCreatureParty = std::vector<BattleState::BattleCreaturePtr>;

    class BattleCreatureAI : public BattleState::BattleCreature {
    private:
        const BattleCreatureParty &enemyParty;
        std::shared_ptr<BattleCreature> target;
    public:
        BattleCreatureAI(int id, const int creature, const BattleCreatureParty &enemies) : BattleCreature(id, creature),
                                                                                           enemyParty(enemies) { }

        const std::shared_ptr<BattleCreature> &getTarget() const { return target; }

        void setTarget(const std::shared_ptr<BattleCreature> &target) { BattleCreatureAI::target = target; }

        void updateTarget();
    };

}

#endif //FAMILY_BUSINESS_BATTLECREATUREAI_H
