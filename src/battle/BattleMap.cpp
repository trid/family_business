//
// Created by TriD on 22.06.2015.
//

#include <cstdlib>

#include "BattleMap.h"

using namespace MEng;

BattleMap::BattleMap() {
    mapData.resize(width);

    for (auto& item: mapData) {
        item.resize(height);
    }
}

void BattleMap::calculateMoveable(BattleCreaturePtr creature) {
    //TODO: Change to Dijkstra algorithm when landscape become complicated
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++) {
            Point diff = creature->getPosition() - Point{x, y};
            int dist = std::abs(diff.x) + std::abs(diff.y);
            mapData[x][y].setCanMove(dist < creature->getSteps() && dist != 0);
        }
    }
}
