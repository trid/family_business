//
// Created by TriD on 24.05.2015.
//

#include <algorithm>

#include "MainState.h"
#include "CharacterManager.h"
#include "Game.h"
#include "../Application.h"
#include "../battle/BattleState.h"
#include "Monster.h"
#include "../MessageManager.h"
#include "FamilyManager.h"
#include "HouseManager.h"

MainState::MainState() {
    ViewPtr view{new MainView()};
    setView(view);
    MessageListenerPtr listenerPtr{new CharacterWinListener};
    MessageListenerPtr movementListener{new CharacterMovedListener};
    MessageManager &messageManager = MessageManager::getInstance();
    messageManager.addListener("player_win", listenerPtr);
    messageManager.addListener("movement_finished", movementListener);
}

void MainState::onClick(const Point &point, int button) {
    State::onClick(point, button);
}

void MainState::onActivate() {
    State::onActivate();
}

void MainState::run() {
    State::run();

    unsigned int ticks = SDL_GetTicks();
    unsigned int delta = ticks - lastTime;
    lastTime = ticks;
    getView()->update(delta);

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

void MainState::onKeyDown(int keyCode) {
    State::onKeyDown(keyCode);
    getView()->onKeyDown(keyCode);

    if (getView()->getLayout().isDialogActive()) {
        return;
    }

    Party& playerParty = Game::getInstance().getPlayerParty();
    GameMap& gameMap = Game::getInstance().getMap();
    if (keyCode == SDLK_UP || keyCode == SDLK_DOWN || keyCode == SDLK_LEFT || keyCode == SDLK_RIGHT) {
        int posX = playerParty.getX();
        int posY = playerParty.getY();
        bool startedMovement{false};

        switch (keyCode) {
            case SDLK_UP:
                if (posY > 0) {
                    --posY;
                    startedMovement = true;
                }
                break;
            case SDLK_DOWN:
                if (posY < 127) {
                    ++posY;
                    startedMovement = true;
                }
                break;
            case SDLK_RIGHT:
                if (posX < 127) {
                    ++posX;
                    startedMovement = true;
                }
                break;
            case SDLK_LEFT:
                if (posX > 0) {
                    --posX;
                    startedMovement = true;
                }
                break;
            default:
                break;
        }

        if (startedMovement && !playerParty.isMoving()) {
            MessageParameters parameters;
            parameters.setParameter("dx", posX - playerParty.getX());
            parameters.setParameter("dy", posY - playerParty.getY());
            MessageManager::getInstance().sendMessage("party_moving", parameters);
            MovementPtr movementPtr{new Movement{playerParty, {posX, posY}}};
            movement.push_back(movementPtr);
            playerParty.setMoving(true);
        }
    }
    if (keyCode == SDLK_SPACE) {
        int houseId = gameMap.getTile(playerParty.getX(), playerParty.getY()).getHouse();
        if (houseId != -1) {
            if (getHouseById(houseId).getSide() == Side::Player) {
                takeMercenary();
            }
            else {
                battleMonsters();
            }
        }
    }
}

void MainState::onKeyUp(int keyCode) {
    State::onKeyUp(keyCode);
}

void MainState::takeMercenary() {
    Game &game = Game::getInstance();
    Party& playerParty = game.getPlayerParty();
    int houseId = game.getMap().getTile(playerParty.getX(), playerParty.getY()).getHouse();
    if (houseId) {
        static_cast<MainView*>(getView().get())->showHireDialog(getHouseById(houseId));
    }
}

void MainState::battleMonsters() {
    int partyId = PartyManager::getInstance().createParty(Side::AI);
    Party& party = PartyManager::getInstance().getParty(partyId);
    // Yes, it's not so beautiful, but as is for now
    /*partyPtr->addCreature(std::make_shared<Monster>());
    partyPtr->addCreature(std::make_shared<Monster>());
    partyPtr->addCreature(std::make_shared<Monster>());*/
    party.addCreature(CreatureManager::getInstance().createMonster());

    Application::getInstance().pushState(std::make_shared<BattleState>(Game::getInstance().getPlayerParty(), party));
}

void MainState::CharacterWinListener::onMessage(const MessageParameters &messageParameters) {
    Game& game = Game::getInstance();
    Party& party = game.getPlayerParty();
    GameMap& gameMap = game.getMap();
    int houseId = gameMap.getTile(party.getX(), party.getY()).getHouse();

    if (houseId && getHouseById(houseId).getSide() == Side::AI) {
        Character& character = game.getPlayerCharacter();
        character.addItem(ItemPtr{new Item(ItemType::Armor, 1)});
    }
}

void MainState::CharacterMovedListener::onMessage(const MessageParameters &messageParameters) {
    Game& game = Game::getInstance();
    GameMap &gameMap = game.getMap();
    Party& playerParty = game.getPlayerParty();

    gameMap.getTile(playerParty.getX(), playerParty.getY()).setParty(-1);
    int posX = messageParameters.getParameter("x").getInt();
    playerParty.setX(posX);
    int posY = messageParameters.getParameter("y").getInt();
    playerParty.setY(posY);

    int partyId = gameMap.getTile(posX, posY).getParty();
    PartyManager &partyManager = PartyManager::getInstance();
    if (partyId != -1 && partyManager.getParty(partyId).getSide() == Side::AI) {
        Application::getInstance().pushState(StatePtr{new BattleState(playerParty, partyManager.getParty(partyId))});
        return;
    }

    gameMap.getTile(posX, posY).setParty(playerParty.getId());

    MessageManager::getInstance().sendMessage("character_moved", messageParameters);
}

void MainState::onPop() {
    State::onPop();

    FamilyManager::getInstance().clear();
    CreatureManager::getInstance().clear();
    PartyManager::getInstance().clear();
    HouseManager::getInstance().clear();
    MessageManager::getInstance().clear();
}

void MainState::save(std::ofstream &out) {
    int size = movement.size();
    out.write((char*)&size, sizeof(size));

    for (auto& item: movement) {
        item->save(out);
    }
}

void MainState::load(std::ifstream &in) {
    int size{};
    in.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (int i = 0; i < size; i++) {
        movement.emplace_back(new Movement(in));
    }
}
