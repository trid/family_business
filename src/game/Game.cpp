//
// Created by TriD on 14.06.2015.
//

#include "Game.h"
#include "FamilyManager.h"
#include "RandomMapGenerator.h"

Game::Game() {
    const Families& families = FamilyManager::getInstance().getFamilies();

    RandomMapGenerator(gameMap).createMap(gameMap);

    for (auto& family: families) {
        gameMap.createHouse(family->getId());
    }
}
