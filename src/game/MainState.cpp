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

MainState::MainState() {
    ViewPtr view{new MainView()};
    setView(view);
    MessageListenerPtr listenerPtr{new CharacterWinListener};
    MessageListenerPtr movementListener{new CharacterMovedListener};
    MessageManager &messageManager = MessageManager::getInstance();
    messageManager.addListener("player_win", listenerPtr);
    messageManager.addListener("character_moved", movementListener);
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
}

void MainState::onKeyDown(int keyCode) {
    State::onKeyDown(keyCode);
    getView()->onKeyDown(keyCode);

    if (getView()->getLayout().isDialogActive()) {
        return;
    }

    PartyPtr playerParty = Game::getInstance().getPlayerParty();
    GameMap& gameMap = Game::getInstance().getMap();
    if (keyCode == SDLK_UP || keyCode == SDLK_DOWN || keyCode == SDLK_LEFT || keyCode == SDLK_RIGHT) {
        if (!playerParty) return;
        int posX = playerParty->getX();
        int posY = playerParty->getY();

        switch (keyCode) {
            case SDLK_UP:
                --posY;
                break;
            case SDLK_DOWN:
                ++posY;
                break;
            case SDLK_RIGHT:
                ++posX;
                break;
            case SDLK_LEFT:
                --posX;
                break;
            default:
                break;
        }

        if (!playerParty->isMoving()) {
            MessageManager::getInstance().sendMessage("party_moving", MessageParameters());
            MovementPtr movementPtr{new Movement{playerParty, {posX, posY}}};
            movement.push_back(movementPtr);
            playerParty->setMoving(true);
        }
    }
    if (keyCode == SDLK_SPACE) {
        const HousePtr &house = gameMap.getTile(playerParty->getX(), playerParty->getY()).getHouse();
        if (house) {
            if (house->getSide() == Side::Player) {
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
    getView()->onKeyUp(keyCode);
}

void MainState::takeMercenary() {
    Game &game = Game::getInstance();
    PartyPtr playerParty = game.getPlayerParty();
    HousePtr housePtr = game.getMap().getTile(playerParty->getX(), playerParty->getY()).getHouse();
    if (housePtr) {
        static_cast<MainView*>(getView().get())->showHireDialog(housePtr);
    }
}

void MainState::battleMonsters() {
    PartyPtr partyPtr = std::make_shared<Party>(Side::AI);
    // Yes, it's not so beautiful, but as is for now
    /*partyPtr->addCreature(std::make_shared<Monster>());
    partyPtr->addCreature(std::make_shared<Monster>());
    partyPtr->addCreature(std::make_shared<Monster>());*/
    partyPtr->addCreature(CreatureManager::getInstance().createMonster());

    Application::getInstance().pushState(std::make_shared<BattleState>(Game::getInstance().getPlayerParty(), partyPtr));
}

void MainState::CharacterWinListener::onMessage(const MessageParameters &messageParameters) {
    Game& game = Game::getInstance();
    PartyPtr partyPtr = game.getPlayerParty();
    GameMap& gameMap = game.getMap();
    HousePtr housePtr = gameMap.getTile(partyPtr->getX(), partyPtr->getY()).getHouse();

    if (housePtr && housePtr->getSide() == Side::AI) {
        Character& character = game.getPlayerCharacter();
        character.addItem(ItemPtr{new Item(ItemType::Armor, 1)});
    }
}

void MainState::CharacterMovedListener::onMessage(const MessageParameters &messageParameters) {
    Game& game = Game::getInstance();
    GameMap &gameMap = game.getMap();
    PartyPtr playerParty = game.getPlayerParty();

    gameMap.getTile(playerParty->getX(), playerParty->getY()).setParty(nullptr);
    int posX = messageParameters.getParameter("x").getInt();
    playerParty->setX(posX);
    int posY = messageParameters.getParameter("y").getInt();
    playerParty->setY(posY);

    PartyPtr party = gameMap.getTile(posX, posY).getParty();
    if (party && party->getSide() == Side::AI) {
        Application::getInstance().pushState(StatePtr{new BattleState(playerParty, party)});
        return;
    }

    gameMap.getTile(posX, posY).setParty(playerParty);
}
