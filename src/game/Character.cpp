//
// Created by TriD on 24.05.2015.
//

#include "Character.h"

Character::Character(const string &name, const string &lastName, Gender gender, FamilyPtr family) :
    Creature(15, 5, 6),
    name(name), lastName(lastName), gender(gender), familyPtr(family)
{

}

void Character::equip(ItemPtr item) {
    if (item->getType() == ItemType::Armor) {
        if (armor) {
            unequipArmor();
        }
        setDefence(getDefence() + item->getLevel());
    }
}

void Character::unequipArmor() {
    if (armor) {
        setDefence(getDefence() - armor->getLevel());
        armor = nullptr;
    }
}
