//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTER_H
#define FAMILY_BUSINESS_CHARACTER_H

#include <memory>
#include <string>

#include "Creature.h"

class Family;

using std::string;
using FamilyPtr = std::shared_ptr<Family>;


enum class Gender{Male, Female};


class Character: public Creature {
    string name;

    string lastName;
    Gender gender;

    FamilyPtr familyPtr;
public:
    Character(const string &name, const string &lastName, Gender gender, FamilyPtr family);

    const string& getName() { return name; }
    const string& getLastName() { return lastName; }
    Gender getGender() { return gender; }
    FamilyPtr getFamily() { return familyPtr; }
};


#endif //FAMILY_BUSINESS_CHARACTER_H
