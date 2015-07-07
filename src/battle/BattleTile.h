//
// Created by TriD on 23.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLETILE_H
#define FAMILY_BUSINESS_BATTLETILE_H

#include <memory>

#include "BattleCreature.h"

class BattleTile {
private:
    BattleCreaturePtr creature;
public:
    const BattleCreaturePtr &getCreature() const { return creature; }
    void setCreature(const BattleCreaturePtr &creature) { BattleTile::creature = creature; }
};


#endif //FAMILY_BUSINESS_BATTLETILE_H
