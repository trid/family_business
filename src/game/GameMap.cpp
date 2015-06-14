//
// Created by TriD on 24.05.2015.
//

#include "GameMap.h"

#include <ctime>
#include <random>

GameMap::GameMap() {
    mapData.resize(width);
    for (auto& item: mapData) {
        item.resize(height);
        for (auto& tile: item) {
            tile = TilePtr{new Tile()};
        }
    }
    std::default_random_engine generator{};
    generator.seed(std::time(0));
    std::uniform_int_distribution<int> widthDistribution{0, width - 1};
    std::uniform_int_distribution<int> heightDistribution{0, height - 1};
    int housePosX = widthDistribution(generator);
    int housePosY = heightDistribution(generator);
    mapData[housePosX][housePosY]->setHouse(HousePtr(new House));
}
