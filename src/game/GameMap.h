//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_GAMEMAP_H
#define FAMILY_BUSINESS_GAMEMAP_H

#include <vector>

#include "Tile.h"
#include "Village.h"

using ColumnData = std::vector<Tile>;
using MapData = std::vector<ColumnData>;

class GameMap {
private:
    MapData mapData;
    unsigned int width{128};
    unsigned int height{128};

    Village village;
public:
    GameMap();

    unsigned int getWidth() { return width; }
    unsigned int getHeight() { return height; }

    Tile& getTile(int x, int y) { return mapData[x][y]; }
    Tile& getTile(Point point) { return mapData[point.x][point.y]; }
    int getHousePosX() { return village.getCenter().x; }
    int getHousePosY() { return village.getCenter().y; }

    void createHouse(int familyId);
};


#endif //FAMILY_BUSINESS_GAMEMAP_H
