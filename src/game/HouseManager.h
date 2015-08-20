//
// Created by TriD on 20.08.2015.
//

#ifndef FAMILY_BUSINESS_HOUSEMANAGER_H
#define FAMILY_BUSINESS_HOUSEMANAGER_H

#include <memory>
#include <vector>
#include "House.h"

using HousePtr = std::unique_ptr<House>;
using Houses = std::vector<HousePtr>;

class HouseManager {
private:
    Houses houses;
    HouseManager(){}
public:
    static HouseManager& getInstance() {
        static HouseManager houseManager;
        return houseManager;
    }

    House& getHouse(int id) { return *houses[id]; }
    int createHouse(int x, int y, Side side) { houses.emplace_back(new House(x, y, side, houses.size()));
        return houses.size() - 1; }
    void clear() { houses.clear(); }
};

inline House& getHouseById(int id) {
    return HouseManager::getInstance().getHouse(id);
}

#endif //FAMILY_BUSINESS_HOUSEMANAGER_H
