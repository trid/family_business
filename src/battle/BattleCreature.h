//
// Created by TriD on 27.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLECREATURE_H
#define FAMILY_BUSINESS_BATTLECREATURE_H

#include <memory>

#include "../Point.h"
#include "../game/CreatureManager.h"


class BattleCreature {
private:
    int currentHp;
    Point position;
    int steps{0};
    int creatureId;
public:
    BattleCreature(int creature);

    int getSpeed() { return getCreature().getSpeed(); }
    int getAttack() { return getCreature().getAttack(); }

    Creature::Type getType() { return getCreature().type(); }
    const Point &getPosition() const { return position; }
    void setPosition(const Point &position) { BattleCreature::position = position; }
    int getSteps() const { return steps; }
    void setSteps(int steps) { BattleCreature::steps = steps; }
    void resetSteps() { steps = getSpeed(); }
    int getCurrentHp() const { return currentHp; }

    void takeDamage(int damage);
    bool isDead() { return currentHp == 0; }
    Creature& getCreature() { return CreatureManager::getInstance().getCreatureById(creatureId); }
    int getCreatureId() { return creatureId; }
};

using BattleCreaturePtr = std::shared_ptr<BattleCreature>;

#endif //FAMILY_BUSINESS_BATTLECREATURE_H
