//
// Created by TriD on 24.05.2015.
//

#include "GameMap.h"
#include "Game.h"
#include "FamilyManager.h"
#include "BuildingManager.h"
#include "MonsterAI.h"
#include "AIManager.h"
#include "../Point.h"

#include <ctime>
#include <random>
#include <unordered_set>

using namespace Main;

GameMap::GameMap() {
    mapData.resize(width);
    for (auto& item: mapData) {
        item.resize(height);
    }
    std::default_random_engine generator{};
    generator.seed(std::time(0));
    std::uniform_int_distribution<unsigned int> widthDistribution{0, width - 1};
    std::uniform_int_distribution<unsigned int> heightDistribution{0, height - 1};
    int centerPosX = widthDistribution(generator);
    int centerPosY = heightDistribution(generator);
    village.setCenter({centerPosX, centerPosY});
    mapData[centerPosX][centerPosY].setBuilding(
            BuildingManager::getInstance().createBuilding(centerPosX, centerPosY, BuildingType::Road));

    //Set monster five tiles on north or five tiles on south of house
    int monsterPartyId = PartyManager::getInstance().createParty(Side::AI);
    MonsterAIPtr monsterAI = std::make_shared<MonsterAI>(monsterPartyId);
    AIManager::getInstance().addAi(monsterAI);
    Party& monsterParty = PartyManager::getInstance().getParty(monsterPartyId);
    monsterParty.addCreature(CreatureManager::getInstance().createMonster());
    //Create monsters den
    BuildingManager &houseManager = BuildingManager::getInstance();
    int houseId = houseManager.createBuilding(centerPosX, 0, BuildingType::MonsterLair);
    Building & house = houseManager.getBuilding(houseId);
    monsterParty.setX(centerPosX);
    if (centerPosY - 5 >= 0) {
        monsterParty.setY(centerPosY - 5);
        house.setY(centerPosY - 4);
        mapData[centerPosX][centerPosY - 5].setParty(monsterParty.getId());
    }
    else {
        monsterParty.setY(centerPosY + 5);
        house.setY(centerPosY + 4);
        mapData[centerPosX][centerPosY + 5].setParty(monsterParty.getId());
    }
    mapData[house.getX()][house.getY()].setBuilding(houseId);
}

void GameMap::createHouse(int familyId) {
    while (checkNeedRoad()) {
        placeRoad();
    }
    if (distributor(generator) == 1) {
        placeRoad();
    }

    auto pointHash = [this](const Point& point) { return point.y * width + point.x; };

    std::unordered_set<Point, decltype(pointHash)> queuedTiles(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> usedTiles(0, pointHash);

    const Point &startPoint = village.getCenter();
    queuedTiles.insert(startPoint);

    while (!queuedTiles.empty()) {
        Point point = *queuedTiles.begin();
        queuedTiles.erase(point);
        if (mapData[point.x][point.y].getBuilding() == -1) {
            int houseId = BuildingManager::getInstance().createBuilding(point.x, point.y, BuildingType::Home);
            Building & house = BuildingManager::getInstance().getBuilding(houseId);
            house.setFamily(familyId);
            mapData[point.x][point.y].setBuilding(houseId);
            getFamilyById(familyId).setHome(houseId);
            break;
        }

        usedTiles.insert(point);

        if (getBuildingType(point) != BuildingType::Road) {
            continue;
        }

        int top = point.y - 1;
        int bottom = point.y + 1;
        int left = point.x - 1;
        int right = point.x + 1;

        if (top >= 0) {
            queuedTiles.insert(Point{point.x, top});
        }
        if (bottom < height) {
            queuedTiles.insert(Point{point.x, bottom});
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

void GameMap::load(std::ifstream &in) {
    in.read((char*)&width, sizeof(width));
    in.read((char*)&height, sizeof(height));
    village.load(in);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            mapData[x][y].load(in);
        }
    }
}

bool GameMap::checkNeedRoad() {
    auto pointHash = [this](const Point& point) { return point.y * width + point.x; };
    std::unordered_set<Point, decltype(pointHash)> pool(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> passed(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> freeTiles(0, pointHash);

    pool.insert(village.getCenter());

    while (!pool.empty()) {
        Point point = *pool.begin();
        pool.erase(point);
        passed.insert(point);

        int left = point.x - 1;
        int right = point.x + 1;
        int top = point.y - 1;
        int bottom = point.y + 1;

        if (left >= 0) {
            BuildingType bt = getBuildingType({left, point.y});
            if (bt == BuildingType::None) freeTiles.insert({left, point.y});
            if (bt == BuildingType::Road) pool.insert({left, point.y});
        }
        if (right < width) {
            BuildingType bt = getBuildingType({right, point.y});
            if (bt == BuildingType::None) freeTiles.insert({right, point.y});
            if (bt == BuildingType::Road) pool.insert({right, point.y});
        }
        if (top >= 0) {
            BuildingType bt = getBuildingType({point.x, top});
            if (bt == BuildingType::None) freeTiles.insert({point.x, top});
            if (bt == BuildingType::Road) pool.insert({point.x, top});
        }
        if (bottom < height) {
            BuildingType bt = getBuildingType({point.x, bottom});
            if (bt == BuildingType::None) freeTiles.insert({point.x, bottom});
            if (bt == BuildingType::Road) pool.insert({point.x, bottom});
        }

        if (freeTiles.size() >= 2) return false;

        for (auto& item: passed) {
            pool.erase(item);
        }
    }

    return true;
}

BuildingType GameMap::getBuildingType(Point p) {
    int buildingId = mapData[p.x][p.y].getBuilding();
    if (buildingId == -1) {
        return BuildingType::None;
    }
    return BuildingManager::getInstance().getBuilding(buildingId).getType();
}

void GameMap::placeRoad() {
    auto pointHash = [this](const Point& point) { return point.y * width + point.x; };
    std::unordered_set<Point, decltype(pointHash)> pool(0, pointHash);
    std::unordered_set<Point, decltype(pointHash)> passed(0, pointHash);
    BuildingManager &buildingManager = BuildingManager::getInstance();

    pool.insert(village.getCenter());

    while (!pool.empty()) {
        Point point = *pool.begin();
        pool.erase(point);
        passed.insert(point);

        int left = point.x - 1;
        int right = point.x + 1;
        int top = point.y - 1;
        int bottom = point.y + 1;

        if (left >= 0) {
            BuildingType bt = getBuildingType({left, point.y});
            if (bt == BuildingType::None) {
                mapData[left][point.y].setBuilding(buildingManager.createBuilding(left, point.y, BuildingType::Road));
                return;
            }
            if (bt == BuildingType::Road) pool.insert({left, point.y});
        }
        if (right < width) {
            BuildingType bt = getBuildingType({right, point.y});
            if (bt == BuildingType::None) {
                mapData[right][point.y].setBuilding(buildingManager.createBuilding(right, point.y, BuildingType::Road));
                return;
            }
            if (bt == BuildingType::Road) pool.insert({right, point.y});
        }
        if (top >= 0) {
            BuildingType bt = getBuildingType({point.x, top});
            if (bt == BuildingType::None) {
                mapData[point.x][top].setBuilding(buildingManager.createBuilding(point.x, top, BuildingType::Road));
                return;
            }
            if (bt == BuildingType::Road) pool.insert({point.x, top});
        }
        if (bottom < height) {
            BuildingType bt = getBuildingType({point.x, bottom});
            if (bt == BuildingType::None) {
                mapData[point.x][top].setBuilding(buildingManager.createBuilding(point.x, bottom, BuildingType::Road));
                return;
            }
            if (bt == BuildingType::Road) pool.insert({point.x, bottom});
        }

        for (auto item: passed) {
            pool.erase(item);
        }
    }
}
