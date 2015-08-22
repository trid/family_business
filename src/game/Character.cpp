//
// Created by TriD on 24.05.2015.
//

#include "Character.h"

Character::Character(const string &name, const string &lastName, Gender gender, int familyId) :
    Creature(15, 5, 6),
    name(name), lastName(lastName), gender(gender), familyId(familyId)
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
        armor = item;
    }
    else {
        if (weapon) {
            unequipWeapon();
        }
        setAttack(getAttack() + item->getLevel());
        weapon = item;
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

void Character::save(std::ofstream &out) {
    Creature::save(out);
    int nameLen = name.size();
    out.write((char*)&nameLen, sizeof(nameLen));
    out.write((char*)name.c_str(), nameLen);
    nameLen = lastName.size();
    out.write((char*)&nameLen, sizeof(nameLen));
    out.write((char*)lastName.c_str(), nameLen);
    out.write((char*)&gender, sizeof(gender));
    out.write((char*)&age, sizeof(age));
    out.write((char*)&familyId, sizeof(familyId));
    int itemsCount = inventory.size();
    out.write((char*)&itemsCount, sizeof(itemsCount));

    for (auto item: inventory) {
        item->save(out);
    }

    int weaponNum{-1};
    int armorNum{-1};

    for (int i = 0; i < inventory.size(); i++) {
        if (weapon == inventory[i]) {
            weaponNum = i;
        }
        if (armor == inventory[i]) {
            armorNum = i;
        }
    }

    out.write((char*)&weaponNum, sizeof(weaponNum));
    out.write((char*)&armorNum, sizeof(armorNum));
}
