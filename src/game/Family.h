//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_FAMILY_H
#define FAMILY_BUSINESS_FAMILY_H

#include <memory>
#include <string>
#include <vector>

#include "Character.h"
#include "CreatureManager.h"

class Character;

class House;

using CharacterPtr = std::shared_ptr<Character>;
using Children = std::vector<int>;
using HousePtr = std::shared_ptr<House>;

class Family {
    int id;

    int father;
    int mother;
    Children children;

    HousePtr home;

    std::string lastName;
public:
    Family(int father, int &mother, Children &children) : father(father),
                                                          mother(mother),
                                                          children(std::move(children)) { }

    const std::string &getLastName() { return static_cast<Character&>(getCreatureById(father)).getLastName(); }

    Character& getFather() { return static_cast<Character&>(getCreatureById(father)); }
    int getFatherId() { return father; }
    Character& getMother() { return static_cast<Character&>(getCreatureById(mother)); }
    int getMotherId() { return mother; }
    Children &getChildren() { return children; }

    const HousePtr &getHome() const { return home; }

    void setHome(HousePtr home) { Family::home = home; }

    int getId() const { return id; }
};

using FamilyPtr = std::shared_ptr<Family>;

#endif //FAMILY_BUSINESS_FAMILY_H
