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
