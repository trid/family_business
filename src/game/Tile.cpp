//
// Created by TriD on 24.05.2015.
//

#include "Tile.h"

void Tile::save(std::ofstream &out) {
    out.write((char*)this, sizeof(*this));
}
