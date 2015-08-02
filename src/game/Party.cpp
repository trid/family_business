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
