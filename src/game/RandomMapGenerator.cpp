//
// Created by TriD on 12.08.2015.
//

#include "RandomMapGenerator.h"

using namespace Main;

RandomMapGenerator::RandomMapGenerator(GameMap& gameMap) {
    generator.seed(std::time(0));
    pointsPositionsDistributorX = Distributor(0, gameMap.getWidth() - 1);
    pointsPositionsDistributorY = Distributor(0, gameMap.getHeight() - 1);

    for (int i = 0; i < higherCount; i++) {
        Point point{pointsPositionsDistributorX(generator), pointsPositionsDistributorY(generator)};
        LandscapeType landscapeType = i < higherCount / 2 ? LandscapeType::None : LandscapeType::Forest;
        higher.emplace_back(point, landscapeType);
    }

    for (int i = 0; i < lowerCount; i++) {
        Point point{pointsPositionsDistributorX(generator), pointsPositionsDistributorY(generator)};
        LandscapeType landscapeType = closestPoint(point, higher).second;
        lower.emplace_back(point, landscapeType);
    }
}

std::pair<Point, LandscapeType> RandomMapGenerator::closestPoint(Point point,
                                                                 const std::vector<std::pair<Point, LandscapeType>> &items) {
    std::pair<Point, LandscapeType> closest = items[0];
    Point dist = closest.first - point;
    int closestDist = abs(dist.x) + abs(dist.y);

    for (auto item: items) {
        Point vdist = item.first - point;
        int currentDist = abs(vdist.x) + abs(vdist.y);
        if (currentDist < closestDist) {
            closest = item;
            closestDist = currentDist;
        }
    }
    return closest;
}

void RandomMapGenerator::createMap(GameMap &gameMap) {
    for (int i = 0; i < gameMap.getWidth(); i++) {
        for (int k = 0; k < gameMap.getHeight(); k++) {
            Point point{i, k};
            auto closest = closestPoint(point, lower);
            gameMap.getTile(point).setLandscapeType(closest.second);
        }
    }
}
