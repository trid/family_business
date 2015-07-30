//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTER_H
#define FAMILY_BUSINESS_CHARACTER_H

#include <memory>
#include <string>

#include "Creature.h"
#include "Item.h"

class Family;

using std::string;
using FamilyPtr = std::shared_ptr<Family>;
using Items = std::vector<ItemPtr>;

enum class Gender{Male, Female};


class Character: public Creature {
    string name;

    string lastName;
    Gender gender;
    int age;

    FamilyPtr familyPtr;

    Items inventory;
    ItemPtr armor{nullptr};
    ItemPtr weapon{nullptr};
public:
    Character(const string &name, const string &lastName, Gender gender, FamilyPtr family);

    const string& getName() { return name; }
    const string& getLastName() { return lastName; }
    Gender getGender() { return gender; }
    FamilyPtr getFamily() { return familyPtr; }
    void addItem(ItemPtr item) { inventory.push_back(item); }

    void equip(ItemPtr item);
    void unequipArmor();
    void unequipWeapon();

    virtual Type type() { return Type::Character; }
    ItemPtr getWeapon() { return weapon; }
};


#endif //FAMILY_BUSINESS_CHARACTER_H
