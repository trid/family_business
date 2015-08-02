//
// Created by TriD on 02.08.2015.
//

#ifndef FAMILY_BUSINESS_MOVEMENT_H
#define FAMILY_BUSINESS_MOVEMENT_H


#include "Party.h"
#include "../Point.h"

class Movement {
private:
    PartyPtr party;
    Point target;
    int time{0};
public:
    Movement(PartyPtr party, Point target): party(party), target(target) {}
    void update(int delta);
    bool isFinished() { return time >= 500; }
};

using MovementPtr = std::shared_ptr<Movement>;

#endif //FAMILY_BUSINESS_MOVEMENT_H
