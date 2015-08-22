//
// Created by TriD on 24.05.2015.
//

#include "GameMap.h"
#include "Game.h"
#include "Monster.h"
#include "FamilyManager.h"
#include "HouseManager.h"

#include <ctime>
#include <random>
#include <unordered_set>

GameMap::GameMap() {
    mapData.resize(width);
    for (auto& item: mapData) {
        item.resize(height);
    }
    std::default_random_engine generator{};
    generator.seed(std::time(0));
    std::uniform_int_distribution<unsigned int> widthDistribution{0, width - 1};
    std::uniform_int_distribution<unsigned int> heightDistribution{0, height - 1};
    int housePosX = widthDistribution(generator);
    int housePosY = heightDistribution(generator);
    village.setCenter({housePosX, housePosY});

    //Set monster five tiles on north or five tiles on south of house
    int monsterPartyId = PartyManager::getInstance().createParty(Side::AI);
    Party& monsterParty = PartyManager::getInstance().getParty(monsterPartyId);
    monsterParty.addCreature(CreatureManager::getInstance().createMonster());
    //Create monsters den
    HouseManager &houseManager = HouseManager::getInstance();
    int houseId = houseManager.createHouse(housePosX, 0, Side::AI);
    House& house = houseManager.getHouse(houseId);
    monsterParty.setX(housePosX);
    if (housePosY - 5 >= 0) {
        monsterParty.setY(housePosY - 5);
        house.setY(housePosY - 4);
        mapData[housePosX][housePosY - 5].setParty(monsterParty.getId());
    }
    else {
        monsterParty.setY(housePosY + 5);
        house.setY(housePosY + 4);
        mapData[housePosX][housePosY + 5].setParty(monsterParty.getId());
    }
    mapData[house.getX()][house.getY()].setHouse(houseId);
}

void GameMap::createHouse(int familyId) {
    auto pointHash = [this](const Point& point) { return point.y * width + point.x; };

    std::unordered_set<Point, decltype(pointHash)> queuedTiles(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> usedTiles(0, pointHash);

    const Point &startPoint = village.getCenter();
    queuedTiles.insert(startPoint);

    while (!queuedTiles.empty()) {
        const Point& point = *queuedTiles.begin();
        if (mapData[point.x][point.y].getHouse() == -1) {
            int houseId = HouseManager::getInstance().createHouse(point.x, point.y, Side::Player);
            House& house = HouseManager::getInstance().getHouse(houseId);
            house.setFamily(familyId);
            mapData[point.x][point.y].setHouse(houseId);
            getFamilyById(familyId).setHome(houseId);
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


void GameMap::save(std::ofstream &out) {
    out.write((char*)&width, sizeof(width));
    out.write((char*)&height, sizeof(height));
    village.save(out);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            mapData[x][y].save(out);
        }
    }
}
