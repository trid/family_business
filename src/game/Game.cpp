//
// Created by TriD on 14.06.2015.
//

#include "Game.h"
#include "FamilyManager.h"

Game::Game() {
    const Families& families = FamilyManager::getInstance().getFamilies();

    for (auto& family: families) {
        gameMap.createHouse(family->getId());
    }
}
