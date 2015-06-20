//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_TILE_H
#define FAMILY_BUSINESS_TILE_H

#include <memory>

#include "House.h"

class Creature;
using CreaturePtr = std::shared_ptr<Creature>;

class Tile {
private:
    HousePtr housePtr{nullptr};
    CreaturePtr creature;
public:
    void setHouse(HousePtr housePtr) { this->housePtr = housePtr; }
    HousePtr getHouse() { return housePtr; }

    const CreaturePtr &getCreature() const { return creature;  }
    void setCreature(const CreaturePtr &creature) { Tile::creature = creature; }
};

using TilePtr = std::shared_ptr<Tile>;

#endif //FAMILY_BUSINESS_TILE_H
