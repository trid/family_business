//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_MONSTER_H
#define FAMILY_BUSINESS_MONSTER_H


#include "Creature.h"


class Monster: public Creature {

public:
    Monster(): Creature(20, 10, 8) {}
    virtual Type type() { return Type::Monster; }
};


#endif //FAMILY_BUSINESS_MONSTER_H
