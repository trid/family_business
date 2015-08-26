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

    //Mark for beginning of character data
    char typeLabel[] = "character";
    out.write(typeLabel, 9);
    int nameLen = name.size();
    out.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
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

void Character::load(std::ifstream &in) {
    //Read character mark
    char typeLabel[10];
    typeLabel[9] = '\0';
    in.read(typeLabel, 9);
    //Load first name and last name is just... fuck.
    int len{0};
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    char* buff = new char[len + 1];
    in.read(buff, len);
    buff[len] = '\0';
    name = buff;
    delete[] buff;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buff = new char[len + 1];
    in.read(buff, len);
    buff[len] = '\0';
    lastName = buff;
    delete[] buff;

    in.read(reinterpret_cast<char*>(&gender), sizeof(gender));
    in.read(reinterpret_cast<char*>(&age), sizeof(age));
    in.read(reinterpret_cast<char*>(&familyId), sizeof(familyId));
    int itemsCount{0};
    in.read(reinterpret_cast<char*>(&itemsCount), sizeof(itemsCount));

    for (int i = 0; i < itemsCount; i++) {
        inventory.emplace_back(new Item(in));
    }

    int weaponNum{0};
    in.read(reinterpret_cast<char*>(&weaponNum), sizeof(weaponNum));
    int armorNum{0};
    in.read(reinterpret_cast<char*>(&armorNum), sizeof(armorNum));

    weapon = weaponNum != -1 ? inventory[weaponNum] : nullptr;
    armor = armorNum != -1 ? inventory[armorNum] : nullptr;
}
