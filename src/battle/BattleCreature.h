//
// Created by TriD on 27.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLECREATURE_H
#define FAMILY_BUSINESS_BATTLECREATURE_H

#include <memory>

#include "../Point.h"
#include "../game/CreatureManager.h"

namespace BattleState {

    class BattleCreature {
    private:
        int id;
        int currentHp;
        MEng::Point position;
        int steps{0};
        int creatureId;
    public:
        BattleCreature(int id, int creature);

        int getSpeed() { return getCreature().getSpeed(); }

        int getAttack() { return getCreature().getAttack(); }

        Main::Side getSide() { return getCreature().getSide(); }

        const MEng::Point &getPosition() const { return position; }

        void setPosition(const MEng::Point &position) { BattleCreature::position = position; }

        int getSteps() const { return steps; }

        void setSteps(int steps) { BattleCreature::steps = steps; }

        void resetSteps() { steps = getSpeed(); }

        int getCurrentHp() const { return currentHp; }

        void takeDamage(int damage);

        bool isDead() { return currentHp == 0; }

        Main::Creature &getCreature() { return Main::CreatureManager::getInstance().getCreatureById(creatureId); }

        int getCreatureId() { return creatureId; }

        int getId() { return id; }
    };

    using BattleCreaturePtr = std::shared_ptr<BattleCreature>;

}
#endif //FAMILY_BUSINESS_BATTLECREATURE_H
