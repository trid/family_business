//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_TILE_H
#define FAMILY_BUSINESS_TILE_H

#include <memory>

#include "House.h"
#include "Party.h"

class Tile {
private:
    HousePtr housePtr{nullptr};
    PartyPtr party;
public:
    void setHouse(HousePtr housePtr) { this->housePtr = housePtr; }
    HousePtr getHouse() { return housePtr; }

    const PartyPtr &getParty() const { return party;  }
    void setParty(const PartyPtr &party) { Tile::party = party; }
};

using TilePtr = std::shared_ptr<Tile>;

#endif //FAMILY_BUSINESS_TILE_H
