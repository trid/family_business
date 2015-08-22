//
// Created by TriD on 18.07.2015.
//

#include "Party.h"

bool Party::addCreature(int creaturePtr) {
    if (creatureIds.size() >= 10) {
        return false;
    }
    creatureIds.push_back(creaturePtr);
    return true;
}

void Party::save(std::ofstream &out) {
    out.write((char*)&id, sizeof(id));
    int count = creatureIds.size();
    out.write((char*)&count, sizeof(count));
    for (int item: creatureIds) {
        out.write((char*)&item, sizeof(int));
    }
    out.write((char*)&side, sizeof(side));
    out.write((char*)&x, sizeof(x));
    out.write((char*)&y, sizeof(y));
    out.write((char*)&moving, sizeof(moving));
}
