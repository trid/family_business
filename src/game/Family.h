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


class House;

using Children = std::vector<int>;

class Family {
    int id;

    int father;
    int mother;
    Children children;

    int home;

    std::string lastName;
public:
    Family(int id, int father, int &mother, Children &children) : id(id), father(father),
                                                          mother(mother),
                                                          children(std::move(children)) { }

    const std::string &getLastName() { return static_cast<Character&>(getCreatureById(father)).getLastName(); }

    Character& getFather() { return static_cast<Character&>(getCreatureById(father)); }
    int getFatherId() { return father; }
    Character& getMother() { return static_cast<Character&>(getCreatureById(mother)); }
    int getMotherId() { return mother; }
    Children &getChildren() { return children; }

    int getHome() const { return home; }
    void setHome(int home) { Family::home = home; }

    int getId() const { return id; }
};

#endif //FAMILY_BUSINESS_FAMILY_H
