//
// Created by TriD on 18.07.2015.
//

#include "Party.h"

using namespace Main;

bool Party::addCreature(int creaturePtr) {
    if (creatureIds.size() >= 10) {
        return false;
    }
    creatureIds.push_back(creaturePtr);
    return true;
}

void Party::save(std::ofstream &out) {
    out.write((char*)&id, sizeof(id));
    out.write(reinterpret_cast<char*>(&controller), sizeof(controller));
    int count = creatureIds.size();
    out.write((char*)&count, sizeof(count));
    for (int item: creatureIds) {
        out.write((char*)&item, sizeof(int));
    }
    out.write((char*)&side, sizeof(side));
    out.write((char*)&position, sizeof(position));
    out.write((char*)&moving, sizeof(moving));
}

void Party::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&controller), sizeof(controller));
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (int i = 0; i < count; i++) {
        int itemId{0};
        in.read(reinterpret_cast<char*>(&itemId), sizeof(itemId));
        creatureIds.push_back(itemId);
    }
    in.read(reinterpret_cast<char*>(&side), sizeof(side));
    in.read(reinterpret_cast<char*>(&position), sizeof(position));
    in.read(reinterpret_cast<char*>(&moving), sizeof(moving));
}
