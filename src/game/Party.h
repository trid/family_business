//
// Created by TriD on 18.07.2015.
//

#ifndef FAMILY_BUSINESS_PARTY_H
#define FAMILY_BUSINESS_PARTY_H

#include <memory>
#include <vector>

#include "Side.h"

#include "Creature.h"


class Party {
private:
    std::vector<int> creatureIds;
    Side side;
    int x, y;
public:
    Party(Side side): side(side) {}
    bool addCreature(int creaturePtr);

    int getX() const { return x; }
    void setX(int x) { Party::x = x; }
    int getY() const { return y; }
    void setY(int y) { Party::y = y; }

    const Side getSide() const { return side; }
    std::vector<int>& getCreatures() { return creatureIds; }
};

using PartyPtr = std::shared_ptr<Party>;

#endif //FAMILY_BUSINESS_PARTY_H
