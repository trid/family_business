//
// Created by TriD on 24.05.2015.
//

#include "MainState.h"
#include "CharacterManager.h"
#include "Game.h"
#include "../Application.h"
#include "../battle/BattleState.h"

MainState::MainState(): view{new MainView()} {

}

void MainState::onClick(const Point &point, int button) {
    State::onClick(point, button);
    view->onClick(point, button);
}

void MainState::onActivate() {
    State::onActivate();
    Screen::getInstance().setView(view);
}

void MainState::run() {
    State::run();

    unsigned int ticks = SDL_GetTicks();
    unsigned int delta = ticks - lastTime;
    lastTime = ticks;
    view->update(delta);
}

void MainState::onKeyDown(int keyCode) {
    State::onKeyDown(keyCode);
    view->onKeyDown(keyCode);

    if (keyCode == SDLK_UP || keyCode == SDLK_DOWN || keyCode == SDLK_LEFT || keyCode == SDLK_RIGHT) {
        CharacterPtr character = Game::getInstance().getPlayerCharacter();
        if (!character) return;
        int posX = character->getX();
        int posY = character->getY();

        GameMap& gameMap = Game::getInstance().getMap();
        gameMap.getTile(posX, posY)->setCreature(nullptr);

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

        character->setX(posX);
        character->setY(posY);

        CreaturePtr creature = gameMap.getTile(posX, posY)->getCreature();
        if (creature && creature->type() != character->type()) {
            Application::getInstance().pushState(StatePtr{new BattleState()});
        }
        
        gameMap.getTile(posX, posY)->setCreature(character);
    }
}

void MainState::onKeyUp(int keyCode) {
    State::onKeyUp(keyCode);
    view->onKeyUp(keyCode);
}
