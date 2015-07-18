//
// Created by TriD on 18.07.2015.
//

#ifndef FAMILY_BUSINESS_PARTY_H
#define FAMILY_BUSINESS_PARTY_H

#include <memory>
#include <vector>

#include "Side.h"

#include "Creature.h"

using CreaturePtr = std::shared_ptr<Creature>;

class Party {
private:
    std::vector<CreaturePtr> creatures;
    Side side;
    int x, y;
public:
    Party(Side side): side(side) {}
    void addCreature(CreaturePtr creaturePtr) { creatures.push_back(creaturePtr); }

    int getX() const { return x; }
    void setX(int x) { Party::x = x; }
    int getY() const { return y; }
    void setY(int y) { Party::y = y; }

    const Side getSide() const { return side; }
    std::vector<CreaturePtr>& getCreatures() { return creatures; }
};

using PartyPtr = std::shared_ptr<Party>;

#endif //FAMILY_BUSINESS_PARTY_H
