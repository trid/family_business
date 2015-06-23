//
// Created by TriD on 22.06.2015.
//

#include "BattleMap.h"

BattleMap::BattleMap(CreaturePtr character, CreaturePtr monster) {
    mapData.resize(width);

    for (auto& item: mapData) {
        item.resize(height);
    }

    mapData[0][0].setCreature(character);
    mapData[width - 1][height - 1].setCreature(monster);
}
