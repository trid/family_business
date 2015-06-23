//
// Created by TriD on 23.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLETILE_H
#define FAMILY_BUSINESS_BATTLETILE_H

#include <memory>

class Creature;

using CreaturePtr = std::shared_ptr<Creature>;

class BattleTile {
private:
    CreaturePtr creature;
public:
    const CreaturePtr &getCreature() const { return creature; }
    void setCreature(const CreaturePtr &creature) { BattleTile::creature = creature; }
};


#endif //FAMILY_BUSINESS_BATTLETILE_H
