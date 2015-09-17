//
// Created by TriD on 24.05.2015.
//

#include "Creature.h"

using namespace Main;

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
    Side creatureSide = getSide();
    out.write((char*)&creatureSide, sizeof(creatureSide));
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
    out.write(reinterpret_cast<char*>(&controller), sizeof(controller));
}

void Creature::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    in.read(reinterpret_cast<char*>(&y), sizeof(y));
    in.read(reinterpret_cast<char*>(&hitPoints), sizeof(hitPoints));
    in.read(reinterpret_cast<char*>(&attack), sizeof(attack));
    in.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    in.read(reinterpret_cast<char*>(&defence), sizeof(defence));
    in.read(reinterpret_cast<char*>(&level), sizeof(level));
    in.read(reinterpret_cast<char*>(&experience), sizeof(experience));
    in.read(reinterpret_cast<char*>(&alive), sizeof(alive));
    in.read(reinterpret_cast<char*>(&controller), sizeof(controller));
}
