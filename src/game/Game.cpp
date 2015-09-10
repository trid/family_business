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
#include "BuildingManager.h"
#include "../MessageManager.h"

using namespace MEng;
using namespace Main;

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
    os.write(reinterpret_cast<char*>(&dateDelta), sizeof(dateDelta));

    int size = movement.size();
    os.write((char*)&size, sizeof(size));

    for (auto& item: movement) {
        item->save(os);
    }

    gameMap.save(os);
    CreatureManager::getInstance().save(os);
    PartyManager::getInstance().save(os);
    FamilyManager::getInstance().save(os);
    BuildingManager::getInstance().save(os);
    MainState& mainState = static_cast<MainState&>(Application::getInstance().getCurrentState());
    mainState.save(os);
    MessageManager::getInstance().save(os);

    os.close();
}

void Game::loadGame() {
    FamilyManager::getInstance().clear();
    CreatureManager::getInstance().clear();
    PartyManager::getInstance().clear();
    BuildingManager::getInstance().clear();
    MessageManager::getInstance().clear();

    std::ifstream is("save.sav", std::ios_base::binary);

    is.read((char*)&playerCharacter, sizeof(playerCharacter));
    is.read((char*)&playerParty, sizeof(playerParty));
    is.read(reinterpret_cast<char*>(&days), sizeof(days));
    is.read(reinterpret_cast<char*>(&dateDelta), sizeof(dateDelta));

    int size{};
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (int i = 0; i < size; i++) {
        movement.emplace_back(new Movement(is));
    }

    gameMap.load(is);
    CreatureManager::getInstance().load(is);
    PartyManager::getInstance().load(is);
    FamilyManager::getInstance().load(is);
    BuildingManager::getInstance().load(is);
    MainState& mainState = static_cast<MainState&>(Application::getInstance().getCurrentState());
    mainState.load(is);
    MessageManager::getInstance().load(is);

    MessageParameters messageParameters = MessageParameters();
    MessageManager::getInstance().enqueuMessage("game_loaded", messageParameters);

    is.close();
}

void Game::addDay() {
    ++days;
    CreatureManager::getInstance().updateAge();
    FamilyManager::getInstance().updateDaily();

    MessageParameters messageParameters;
    MessageManager::getInstance().sendMessage("new_day", messageParameters);
}

void Game::update(int delta) {
    for (auto item: movement) {
        item->update(delta);
    }
    auto iter = std::remove_if(movement.begin(), movement.end(), [](MovementPtr movementPtr){ return movementPtr->isFinished(); });
    movement.erase(iter, movement.end());

    dateDelta += delta;
    if (dateDelta >= 60000) {
        dateDelta -= 60000;
        Game::getInstance().addDay();
    }
}

void Game::moveParty(int partyId, Point newPosition) {
    MessageParameters parameters;
    PartyManager &partyManager = PartyManager::getInstance();
    Party& party = partyManager.getParty(partyId);
    int tilePartyId = gameMap.getTile(newPosition).getParty();
    if (tilePartyId != -1) {
        Party& targetParty = partyManager.getParty(tilePartyId);
        if (party.getSide() == targetParty.getSide()) {
            return;
        }
    }
    parameters.setParameter("dx", newPosition.x - party.getX());
    parameters.setParameter("dy", newPosition.y - party.getY());
    parameters.setParameter("partyId", partyId);
    MessageManager::getInstance().sendMessage("party_moving", parameters);
    MovementPtr movementPtr{new Movement{party, newPosition}};
    movement.push_back(movementPtr);
    party.setMoving(true);
}

void Game::marry(int character1, int character2) {
    CreatureManager &manager = CreatureManager::getInstance();
    Character& charRef1 = static_cast<Character&>(manager.getCreatureById(character1));
    Character& charRef2 = static_cast<Character&>(manager.getCreatureById(character2));
    charRef1.setMarried(true);
    charRef2.setMarried(true);
    charRef1.setPartnerId(character2);
    charRef2.setPartnerId(character1);
    int familyId = FamilyManager::getInstance().createFamily(character1, character2);
    gameMap.createHouse(familyId);
}
