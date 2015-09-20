//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLEMAP_H
#define FAMILY_BUSINESS_BATTLEMAP_H

#include <vector>

#include "BattleTile.h"

namespace BattleState {

    using BattleColumn = std::vector<BattleTile>;
    using BattleMapData = std::vector<BattleColumn>;

    class BattleMap {
    private:
        BattleMapData mapData;
    public:
        static constexpr int width = 15;
        static constexpr int height = 15;

        BattleMap();

        const BattleTile &getTile(int x, int y) const { return mapData[x][y]; }

        BattleTile &getTile(int x, int y) { return mapData[x][y]; }

        void calculateMoveable(BattleState::BattleCreaturePtr creature);
    };

}

#endif //FAMILY_BUSINESS_BATTLEMAP_H
