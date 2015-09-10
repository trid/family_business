//
// Created by TriD on 20.08.2015.
//

#ifndef FAMILY_BUSINESS_HOUSEMANAGER_H
#define FAMILY_BUSINESS_HOUSEMANAGER_H

#include <fstream>
#include <memory>
#include <vector>
#include "Building.h"

using BuildingPtr = std::unique_ptr<Building>;
using Buildings = std::vector<BuildingPtr>;

class BuildingManager {
private:
    Buildings buildings;
    BuildingManager(){}
public:
    static BuildingManager & getInstance() {
        static BuildingManager buidingManager;
        return buidingManager;
    }

    Building &getBuilding(int id) { return *buildings[id]; }
    int createBuilding(int x, int y, BuildingType type) { buildings.emplace_back(new Building(x, y, type, buildings.size()));
        return buildings.size() - 1; }
    void clear() { buildings.clear(); }

    void save(std::ofstream& out);
    void load(std::ifstream& in);
};

inline Building & getHouseById(int id) {
    return BuildingManager::getInstance().getBuilding(id);
}

#endif //FAMILY_BUSINESS_HOUSEMANAGER_H
