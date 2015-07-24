//
// Created by TriD on 27.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLECREATURE_H
#define FAMILY_BUSINESS_BATTLECREATURE_H

#include <memory>

#include "../Point.h"
#include "../game/Creature.h"

using CreaturePtr = std::shared_ptr<Creature>;

class BattleCreature {
private:
    int currentHp;
    Point position;
    int steps{0};
    CreaturePtr creaturePtr;
public:
    BattleCreature(CreaturePtr creature);

    int getSpeed() { return creaturePtr->getSpeed(); }
    int getAttack() { return creaturePtr->getAttack(); }

    Creature::Type getType() { return creaturePtr->type(); }
    const Point &getPosition() const { return position; }
    void setPosition(const Point &position) { BattleCreature::position = position; }
    int getSteps() const { return steps; }
    void setSteps(int steps) { BattleCreature::steps = steps; }
    void resetSteps() { steps = getSpeed(); }
    int getCurrentHp() const { return currentHp; }

    void takeDamage(int damage) { currentHp > damage ? currentHp -= damage: currentHp = 0; }
    bool isDead() { return currentHp == 0; }
    CreaturePtr getCreature() { return creaturePtr; }
};

using BattleCreaturePtr = std::shared_ptr<BattleCreature>;

#endif //FAMILY_BUSINESS_BATTLECREATURE_H
