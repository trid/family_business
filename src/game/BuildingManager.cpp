//
// Created by TriD on 20.08.2015.
//

#include "BuildingManager.h"

void BuildingManager::save(std::ofstream &out) {
    int count = buildings.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));

    for (auto& item: buildings) {
        item->save(out);
    }
}

void BuildingManager::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        buildings.emplace_back(new Building(in));
    }
}
