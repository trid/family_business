//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_ITEM_H
#define FAMILY_BUSINESS_ITEM_H

#include <fstream>
#include <memory>

enum class ItemType {
    Armor,
    Weapon
};

class Item {
private:
    ItemType type;
    bool equiped{false};
    int level;
public:
    Item(const ItemType &type, int level) : type(type), level(level) { }

    bool isEquiped() const { return equiped; }
    void setEquiped(bool equiped) { Item::equiped = equiped; }
    int getLevel() const { return level; }
    const ItemType &getType() const { return type; }

    void save(std::ofstream& out);
};

using ItemPtr = std::shared_ptr<Item>;

#endif //FAMILY_BUSINESS_ITEM_H
