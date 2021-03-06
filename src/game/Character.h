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
#include "Side.h"

namespace Main {

    using std::string;
    using Items = std::vector<ItemPtr>;

    enum class Gender {
        Male, Female
    };


    class Character : public Creature {
        string name;
        string lastName;

        Gender gender;
        Side side;
        int age{0};
        bool married{false};
        int partnerId{-1};

        int familyId;

        bool crafter{false};

        Items inventory;
        ItemPtr armor{nullptr};
        ItemPtr weapon{nullptr};

        //TODO: Remove this after creating items for resources
        int wood;

        Generator generator;
        Distributor deathDistr{0, 100};
    public:
        Character(const string &name, const string &lastName, Gender gender, int family);

        Character(std::ifstream &in) : Creature(in) { load(in); }

        const string &getName() { return name; }

        const string &getLastName() { return lastName; }

        Gender getGender() { return gender; }

        int getFamilyId() { return familyId; }

        void addItem(ItemPtr item) { inventory.push_back(item); }

        //TODO: Remove this after creating resource items
        void addWood() { ++wood; }

        void equip(ItemPtr item);

        void unequipArmor();

        void unequipWeapon();

        virtual Side getSide() { return side; }
        void setSide(Side side) { this->side = side; }

        ItemPtr getWeapon() { return weapon; }

        const Items &getItems() const { return inventory; }

        void addDay();

        int getAge() { return age; }

        void setAge(int age) { this->age = age; }

        bool isMarried() const { return married; }

        void setMarried(bool married) { Character::married = married; }

        int getPartnerId() const { return partnerId; }

        void setPartnerId(int partnerId) { Character::partnerId = partnerId; }

        bool isCrafter() { return crafter; }

        void save(std::ofstream &out) override;

        void load(std::ifstream &in) override;
    };

}

#endif //FAMILY_BUSINESS_CHARACTER_H
