//
// Created by TriD on 18.07.2015.
//

#include "Party.h"

bool Party::addCreature(CreaturePtr creaturePtr) {
    if (creatures.size() >= 10) {
        return false;
    }
    creatures.push_back(creaturePtr);
    return true;
}
