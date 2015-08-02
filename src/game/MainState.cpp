//
// Created by TriD on 24.05.2015.
//

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
    MessageManager::getInstance().addListener("player_win", listenerPtr);
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

        gameMap.getTile(posX, posY).setParty(nullptr);

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

        playerParty->setX(posX);
        playerParty->setY(posY);

        PartyPtr party = gameMap.getTile(posX, posY).getParty();
        if (party && party->getSide() == Side::AI) {
            Application::getInstance().pushState(StatePtr{new BattleState(playerParty, party)});
            return;
        }

        gameMap.getTile(posX, posY).setParty(playerParty);
        MessageParameters parameters;
        parameters.setParameter("x", posX);
        parameters.setParameter("y", posY);
        MessageManager::getInstance().sendMessage("character_moved", parameters);
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
