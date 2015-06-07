//
// Created by TriD on 24.05.2015.
//

#include "Application.h"
#include "view/Screen.h"
#include "EventManager.h"

void Application::run() {
    while (running) {
        Screen::getInstance().draw();
        EventManager::getInstance().process();
        if (!states.empty()) {
            states.back()->run();
        }
    }
}

void Application::pushState(StatePtr state) {
    if (!states.empty()) {
        states.back()->onDeactivate();
    }
    states.push_back(state);
    state->onActivate();
}

void Application::popState() {
    states.back()->onDeactivate();
    if (!states.empty()) {
        states.pop_back();
        states.back()->onActivate();
    }
}
