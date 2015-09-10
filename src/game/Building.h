//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_HOME_H
#define FAMILY_BUSINESS_HOME_H

#include <fstream>
#include <memory>
#include <vector>

#include "Side.h"
#include "Family.h"

enum class BuildingType {
    None,
    Home,
    Road,
    MonsterLair,
    Warehouse
};

class Building {
private:
    int id;
    int x, y;
    int familyId;
    BuildingType type;
    std::vector<int> inside;
public:
    Building(int x, int y, BuildingType type, int id): x(x), y(y), type(type), id(id) { }
    Building(std::ifstream& in) { load(in); }

    int getId() const { return id; }

    int getX() const { return x; }
    void setX(int x) { Building::x = x; }
    int getY() const { return y; }
    void setY(int y) { Building::y = y; }
    const int getFamily() const { return familyId; }
    void setFamily(int familyId);
    std::vector<int>& getCharacters() { return inside; }
    BuildingType getType() { return type; }

    void save(std::ofstream& out);
    void load(std::ifstream& in);
};


#endif //FAMILY_BUSINESS_HOME_H
