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
    int id;
    std::vector<int> creatureIds;
    Side side;
    int x, y;

    bool moving{false};
public:
    Party(Side side, int id) : side(side), id(id) {}
    Party(Party&) = delete;
    Party& operator=(Party&) = delete;
    int getId() { return id; }
    bool addCreature(int creaturePtr);

    int getX() const { return x; }
    void setX(int x) { Party::x = x; }
    int getY() const { return y; }
    void setY(int y) { Party::y = y; }

    const Side getSide() const { return side; }
    std::vector<int>& getCreatures() { return creatureIds; }
    
    bool isMoving() const { return moving; }
    void setMoving(bool moving) { Party::moving = moving; }
};


#endif //FAMILY_BUSINESS_PARTY_H
