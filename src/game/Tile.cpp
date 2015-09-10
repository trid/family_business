//
// Created by TriD on 24.05.2015.
//

#include "Tile.h"

using namespace Main;

void Tile::save(std::ofstream &out) {
    out.write((char*)this, sizeof(*this));
}

void Tile::load(std::ifstream &in) {
    in.read((char*)this, sizeof(*this));
}
