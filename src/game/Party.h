//
// Created by TriD on 18.07.2015.
//

#ifndef FAMILY_BUSINESS_PARTY_H
#define FAMILY_BUSINESS_PARTY_H

#include <fstream>
#include <memory>
#include <vector>

#include "Side.h"

#include "Creature.h"
#include "../Point.h"


class Party {
private:
    int id;
    std::vector<int> creatureIds;
    Side side;
    Point position;

    bool moving{false};
public:
    Party(Side side, int id) : side(side), id(id) {}
    Party(std::ifstream& in) { load(in); }
    Party(Party&) = delete;
    Party& operator=(Party&) = delete;
    int getId() { return id; }
    bool addCreature(int creaturePtr);

    int getX() const { return position.x; }
    void setX(int x) { position.x = x; }
    int getY() const { return position.y; }
    void setY(int y) { position.y = y; }
    Point getPosition() const { return position; }
    void setPosition(Point position) { this->position = position; }

    const Side getSide() const { return side; }
    std::vector<int>& getCreatures() { return creatureIds; }
    
    bool isMoving() const { return moving; }
    void setMoving(bool moving) { Party::moving = moving; }

    void save(std::ofstream &out);
    void load(std::ifstream &in);
};


#endif //FAMILY_BUSINESS_PARTY_H
