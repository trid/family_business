//
// Created by TriD on 26.07.2015.
//

#include "Item.h"

using namespace Main;

void Item::save(std::ofstream &out) {
    out.write((char*)this, sizeof(*this));
}

void Item::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(this), sizeof(*this));
}
