//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_FAMILY_H
#define FAMILY_BUSINESS_FAMILY_H

#include <memory>
#include <string>
#include <vector>

#include "Character.h"

using CharacterPtr = std::shared_ptr<Character>;
using Children = std::vector<CharacterPtr>;

class Family {
    CharacterPtr father;
    CharacterPtr mother;
    Children children;
public:
    Family(CharacterPtr father, CharacterPtr &mother, Children &children) : father(father),
                                                                            mother(mother),
                                                                            children(std::move(children)) { }
    const std::string& getLastName() { return father->getLastName(); }
    CharacterPtr getFather() { return father; }
    CharacterPtr getMother() { return mother; }
    Children& getChildren() { return children; }
};

using FamilyPtr = std::shared_ptr<Family>;

#endif //FAMILY_BUSINESS_FAMILY_H
