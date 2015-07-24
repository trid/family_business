//
// Created by TriD on 24.05.2015.
//

#include "GameMap.h"
#include "Game.h"
#include "Monster.h"

#include <ctime>
#include <random>
#include <unordered_set>

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
    std::uniform_int_distribution<unsigned int> widthDistribution{0, width - 1};
    std::uniform_int_distribution<unsigned int> heightDistribution{0, height - 1};
    int housePosX = widthDistribution(generator);
    int housePosY = heightDistribution(generator);
    village.setCenter({housePosX, housePosY});

    //Set monster five tiles on north or five tiles on south of house
    PartyPtr monsterParty{new Party(Side::AI)};
    CreaturePtr creature{new Monster()};
    monsterParty->addCreature(creature);
    HousePtr housePtr{new House(housePosX, 0, Side::AI)};
    monsterParty->setX(housePosX);
    if (housePosY - 5 >= 0) {
        monsterParty->setY(housePosY - 5);
        housePtr->setY(housePosY - 4);
        mapData[housePosX][housePosY - 5]->setParty(monsterParty);
    }
    else {
        monsterParty->setY(housePosY + 5);
        housePtr->setY(housePosY + 4);
        mapData[housePosX][housePosY + 5]->setParty(monsterParty);
    }
    mapData[housePtr->getX()][housePtr->getY()]->setHouse(housePtr);
}

void GameMap::createHouse(FamilyPtr familyPtr) {
    auto pointHash = [this](const Point& point) { return point.y * width + point.x; };

    std::unordered_set<Point, decltype(pointHash)> queuedTiles(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> usedTiles(0, pointHash);

    const Point &startPoint = village.getCenter();
    queuedTiles.insert(startPoint);

    while (!queuedTiles.empty()) {
        const Point& point = *queuedTiles.begin();
        if (!mapData[point.x][point.y]->getHouse()) {
            const std::shared_ptr<House> &housePtr = std::make_shared<House>(point.x, point.y);
            housePtr->setFamily(familyPtr);
            mapData[point.x][point.y]->setHouse(housePtr);
            familyPtr->setHome(housePtr);
            break;
        }
        usedTiles.insert(point);
        int top = point.y - 1;
        int bottom = point.y + 1;
        int left = point.x - 1;
        int right = point.x + 1;

        if (top >= 0) {
            queuedTiles.insert(Point{point.x, top});
            if (left >= 0) {
                queuedTiles.insert(Point{left, top});
            }
            if (right < width) {
                queuedTiles.insert(Point{right, top});
            }
        }

        if (bottom < height) {
            queuedTiles.insert(Point{bottom, point.y});
            if (left >= 0) {
                queuedTiles.insert(Point{left, bottom});
            }
            if (right < width) {
                queuedTiles.insert(Point{right, bottom});
            }
        }

        if (left >= 0) {
            queuedTiles.insert(Point{left, point.y});
        }
        if (right < width) {
            queuedTiles.insert(Point{right, point.y});
        }

        for (auto& item: usedTiles) {
            queuedTiles.erase(item);
        }
    }
}
