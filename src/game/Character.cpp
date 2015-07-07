//
// Created by TriD on 24.05.2015.
//

#include "Character.h"

Character::Character(const string &name, const string &lastName, Gender gender, FamilyPtr family) :
    Creature(15, 5, 6),
    name(name), lastName(lastName), gender(gender), familyPtr(family)
{

}

