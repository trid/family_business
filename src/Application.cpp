//
// Created by TriD on 24.05.2015.
//

#include "Application.h"
#include "view/Screen.h"
#include "EventManager.h"
#include "MessageManager.h"

using namespace MEng;

void Application::run() {
    while (running) {
        Screen::getInstance().draw();
        EventManager::getInstance().process();
        MessageManager::getInstance().update();
        if (!states.empty()) {
            auto state = states.back();
            state->run();
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
        if (!states.empty()) {
            states.back()->onActivate();
        }
    }
}
