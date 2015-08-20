//
// Created by TriD on 14.06.2015.
//

#include <fstream>

#include "Game.h"
#include "FamilyManager.h"
#include "RandomMapGenerator.h"
#include "PartyManager.h"

Game::Game() {

}

void Game::newGame() {
    FamilyManager& familyManager = FamilyManager::getInstance();

    RandomMapGenerator(gameMap).createMap(gameMap);

    for (int i = 0; i < 3; i++) {
        gameMap.createHouse(familyManager.generateFamily());
    }

    playerParty = PartyManager::getInstance().createParty(Side::Player);
}

void Game::saveGame() {
    std::ofstream os("save.sav");


}
