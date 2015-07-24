//
// Created by TriD on 24.05.2015.
//

#include "Creature.h"

void Creature::addExperience(int experience) {
    this->experience += experience;
    if (this->experience >= level * 100) {
        ++level;
        experience = 0;

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
