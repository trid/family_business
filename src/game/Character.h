//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTER_H
#define FAMILY_BUSINESS_CHARACTER_H

#include <fstream>
#include <memory>
#include <string>

#include "Creature.h"
#include "Item.h"


using std::string;
using Items = std::vector<ItemPtr>;

enum class Gender{Male, Female};


class Character: public Creature {
    string name;
    string lastName;

    Gender gender;
    int age{0};
    bool married{false};
    int partnerId{-1};

    int familyId;

    Items inventory;
    ItemPtr armor{nullptr};
    ItemPtr weapon{nullptr};

    Generator generator;
    Distributor deathDistr{0, 100};
public:
    Character(const string &name, const string &lastName, Gender gender, int family);
    Character(std::ifstream& in): Creature(in) { load(in); }

    const string& getName() { return name; }
    const string& getLastName() { return lastName; }
    Gender getGender() { return gender; }
    int getFamilyId() { return familyId; }
    void addItem(ItemPtr item) { inventory.push_back(item); }

    void equip(ItemPtr item);
    void unequipArmor();
    void unequipWeapon();

    virtual Type type() { return Type::Character; }
    ItemPtr getWeapon() { return weapon; }
    const Items& getItems() const { return inventory; }
    void addDay();
    int getAge() { return age; }
    void setAge(int age) { this->age = age; }

    bool isMarried() const { return married; }
    void setMarried(bool married) { Character::married = married; }
    int getPartnerId() const { return partnerId; }
    void setPartnerId(int partnerId) { Character::partnerId = partnerId; }

    void save(std::ofstream& out) override;
    void load(std::ifstream &in) override;
};


#endif //FAMILY_BUSINESS_CHARACTER_H
