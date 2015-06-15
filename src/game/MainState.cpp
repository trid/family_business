//
// Created by TriD on 24.05.2015.
//

#include "MainState.h"
#include "CharacterManager.h"

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
}

void MainState::onKeyUp(int keyCode) {
    State::onKeyUp(keyCode);
    view->onKeyUp(keyCode);
}
