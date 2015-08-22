//
// Created by TriD on 24.05.2015.
//

#include "Creature.h"

void Creature::addExperience(int experience) {
    this->experience += experience;
    if (this->experience >= level * 100) {
        ++level;
        this->experience = 0;

        switch (skillUpDistributor(generator)){
            case 0:
                ++hitPoints;
                break;
            case 1:
                ++attack;
                break;
            case 2:
                ++speed;
                break;
            default:
                break;
        }
    }
}

void Creature::save(std::ofstream &out) {
    Type creatureType = type();
    out.write((char*)&creatureType, sizeof(creatureType));
    out.write((char*)&id, sizeof(id));
    out.write((char*)&x, sizeof(x));
    out.write((char*)&y, sizeof(y));
    out.write((char*)&hitPoints, sizeof(hitPoints));
    out.write((char*)&attack, sizeof(attack));
    out.write((char*)&speed, sizeof(speed));
    out.write((char*)&defence, sizeof(defence));
    out.write((char*)&level, sizeof(level));
    out.write((char*)&experience, sizeof(experience));
    out.write((char*)&alive, sizeof(alive));
}
