//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_GAMEMAP_H
#define FAMILY_BUSINESS_GAMEMAP_H

#include <vector>

#include "Tile.h"

using ColumnData = std::vector<TilePtr>;
using MapData = std::vector<ColumnData>;

class GameMap {
private:
    MapData mapData;
    unsigned int width{128};
    unsigned int height{128};

    int housePosX;
    int housePosY;
public:
    GameMap();

    unsigned int getWidth() { return width; }
    unsigned int getHeight() { return height; }

    TilePtr getTile(int x, int y) { return mapData[x][y]; }
    int getHousePosX() { return housePosX; }
    int getHousePosY() { return housePosY; }
};


#endif //FAMILY_BUSINESS_GAMEMAP_H
