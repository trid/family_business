//
// Created by TriD on 24.05.2015.
//

#include "Character.h"

Character::Character(const string &name, const string &lastName, Gender gender, FamilyPtr family) :
    Creature(15, 5, 6),
    name(name), lastName(lastName), gender(gender), familyPtr(family)
{
    ItemPtr weapon{new Item{ItemType::Weapon, 1}};
    addItem(weapon);
    equip(weapon);
}

void Character::equip(ItemPtr item) {
    if (item->getType() == ItemType::Armor) {
        if (armor) {
            unequipArmor();
        }
        setDefence(getDefence() + item->getLevel());
    }
    else {
        if (weapon) {
            unequipWeapon();
        }
        setAttack(getAttack() + item->getLevel());
    }
    item->setEquiped(true);
}

void Character::unequipArmor() {
    if (armor) {
        setDefence(getDefence() - armor->getLevel());
        armor->setEquiped(false);
        armor = nullptr;
    }
}

void Character::unequipWeapon() {
    if (weapon) {
        setAttack(getAttack() - weapon->getLevel());
        weapon->setEquiped(false);
        weapon = nullptr;
    }
}
