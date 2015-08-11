//
// Created by TriD on 12.08.2015.
//

#ifndef FAMILY_BUSINESS_RANDOMMAPGENERATOR_H
#define FAMILY_BUSINESS_RANDOMMAPGENERATOR_H

#include <ctime>
#include <random>
#include <utility>
#include <vector>

#include "../Point.h"
#include "LandscapeType.h"
#include "GameMap.h"

using Generator = std::default_random_engine;
using Distributor = std::uniform_int_distribution<int>;

class RandomMapGenerator {
private:
    std::vector<std::pair<Point, LandscapeType>> higher;
    std::vector<std::pair<Point, LandscapeType>> lower;

    static constexpr int higherCount = 8;
    static constexpr int lowerCount = 64;

    Generator generator;
    Distributor binaryDistributor{0, 1};
    Distributor pointsPositionsDistributorX;
    Distributor pointsPositionsDistributorY;

    std::pair<Point, LandscapeType> closestPoint(Point point,
                                                 const std::vector<std::pair<Point, LandscapeType>> &items);
public:
    RandomMapGenerator(GameMap& gameMap);
    void createMap(GameMap& gameMap);
};


#endif //FAMILY_BUSINESS_RANDOMMAPGENERATOR_H
