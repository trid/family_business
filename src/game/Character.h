//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTER_H
#define FAMILY_BUSINESS_CHARACTER_H

#include <string>

#include "Creature.h"


using std::string;


enum Gender{Male, Female};


class Character: public Creature {
    string name;

    string lastName;
    Gender gender;
public:
    Character(const string &name, const string &lastName, Gender gender);

    const string& getName() { return name; }
    const string& getLastName() { return lastName; }
    Gender getGender() { return gender; }
};


#endif //FAMILY_BUSINESS_CHARACTER_H
