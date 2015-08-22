//
// Created by TriD on 26.07.2015.
//

#include "Item.h"

void Item::save(std::ofstream &out) {
    out.write((char*)this, sizeof(*this));
}
