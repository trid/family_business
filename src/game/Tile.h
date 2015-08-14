//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_TILE_H
#define FAMILY_BUSINESS_TILE_H

#include <memory>

#include "House.h"
#include "Party.h"
#include "LandscapeType.h"

class Tile {
private:
    HousePtr housePtr{nullptr};
    int party{-1};
    LandscapeType landscapeType;
public:
    void setHouse(HousePtr housePtr) { this->housePtr = housePtr; }
    HousePtr getHouse() { return housePtr; }
    const int getParty() const { return party;  }
    void setParty(const int party) { Tile::party = party; }
    const LandscapeType &getLandscapeType() const { return landscapeType; }
    void setLandscapeType(const LandscapeType &landscapeType) { Tile::landscapeType = landscapeType; }
};

using TilePtr = std::shared_ptr<Tile>;

#endif //FAMILY_BUSINESS_TILE_H
