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

namespace Main {

    using Generator = std::default_random_engine;
    using Distributor = std::uniform_int_distribution<int>;

    class RandomMapGenerator {
    private:
        std::vector<std::pair<Point, Main::LandscapeType>> higher;
        std::vector<std::pair<Point, Main::LandscapeType>> lower;

        static constexpr int higherCount = 8;
        static constexpr int lowerCount = 64;

        Generator generator;
        Distributor binaryDistributor{0, 1};
        Distributor pointsPositionsDistributorX;
        Distributor pointsPositionsDistributorY;

        std::pair<Point, Main::LandscapeType> closestPoint(Point point,
                                                           const std::vector<std::pair<Point, Main::LandscapeType>> &items);

    public:
        RandomMapGenerator(Main::GameMap &gameMap);

        void createMap(Main::GameMap &gameMap);
    };

}

#endif //FAMILY_BUSINESS_RANDOMMAPGENERATOR_H
