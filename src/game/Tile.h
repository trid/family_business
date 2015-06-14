//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_TILE_H
#define FAMILY_BUSINESS_TILE_H

#include <memory>

#include "House.h"

class Tile {
private:
    HousePtr housePtr{nullptr};
public:
    void setHouse(HousePtr housePtr) { this->housePtr = housePtr; }
    HousePtr getHouse() { return housePtr; }
};

using TilePtr = std::shared_ptr<Tile>;

#endif //FAMILY_BUSINESS_TILE_H
