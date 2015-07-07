//
// Created by TriD on 22.06.2015.
//

#include "BattleMap.h"

BattleMap::BattleMap() {
    mapData.resize(width);

    for (auto& item: mapData) {
        item.resize(height);
    }
}
