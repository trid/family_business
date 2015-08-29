//
// Created by TriD on 14.06.2015.
//

#include <fstream>

#include "Game.h"
#include "FamilyManager.h"
#include "RandomMapGenerator.h"
#include "PartyManager.h"
#include "MainState.h"
#include "../Application.h"
#include "HouseManager.h"
#include "../MessageManager.h"

Game::Game() {

}

void Game::newGame() {
    FamilyManager& familyManager = FamilyManager::getInstance();

    RandomMapGenerator(gameMap).createMap(gameMap);

    for (int i = 0; i < 3; i++) {
        gameMap.createHouse(familyManager.generateFamily());
    }

    playerParty = PartyManager::getInstance().createParty(Side::Player);
    auto view = Application::getInstance().getCurrentState().getView();
    std::shared_ptr<MainView> mainView = std::static_pointer_cast<MainView>(view);
    mainView->showFamiliesDialog();
    MessageParameters messageParameters{};
    MessageManager::getInstance().sendMessage("new_game", messageParameters);
}

void Game::saveGame() {
    std::ofstream os("save.sav", std::ios_base::binary);

    os.write((char*)&playerCharacter, sizeof(playerCharacter));
    os.write((char*)&playerParty, sizeof(playerParty));
    os.write(reinterpret_cast<char*>(&days), sizeof(days));

    gameMap.save(os);
    CreatureManager::getInstance().save(os);
    PartyManager::getInstance().save(os);
    FamilyManager::getInstance().save(os);
    MainState& mainState = static_cast<MainState&>(Application::getInstance().getCurrentState());
    mainState.save(os);
    MessageManager::getInstance().save(os);

    os.close();
}

void Game::loadGame() {
    FamilyManager::getInstance().clear();
    CreatureManager::getInstance().clear();
    PartyManager::getInstance().clear();
    HouseManager::getInstance().clear();
    MessageManager::getInstance().clear();

    std::ifstream is("save.sav", std::ios_base::binary);

    is.read((char*)&playerCharacter, sizeof(playerCharacter));
    is.read((char*)&playerParty, sizeof(playerParty));
    is.read(reinterpret_cast<char*>(&days), sizeof(days));

    gameMap.load(is);
    CreatureManager::getInstance().load(is);
    PartyManager::getInstance().load(is);
    FamilyManager::getInstance().load(is);
    MainState& mainState = static_cast<MainState&>(Application::getInstance().getCurrentState());
    mainState.load(is);
    MessageManager::getInstance().load(is);

    MessageParameters messageParameters = MessageParameters();
    MessageManager::getInstance().enqueuMessage("game_loaded", messageParameters);

    is.close();
}
