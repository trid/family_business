//
// Created by TriD on 24.05.2015.
//

#include <algorithm>

#include "State.h"

using namespace MEng;

void State::addMouseEventListener(MouseEventListenerPtr mouseEventListener) {
    mouseEventListeners.push_back(mouseEventListener);
}

void State::addKeyboardEventListener(KeyboardEventListenerPtr keyboardEventListener) {
    keyboardEventListeners.push_back(keyboardEventListener);
}

void State::removeMouseEventListener(MouseEventListenerPtr mouseEventListener) {
    std::remove(mouseEventListeners.begin(), mouseEventListeners.end(), mouseEventListener);
}

void State::removeKeyboardEventListener(KeyboardEventListenerPtr keyboardEventListener) {
    std::remove(keyboardEventListeners.begin(), keyboardEventListeners.end(), keyboardEventListener);
}

void State::clearListeners() {
    keyboardEventListeners.clear();
    mouseEventListeners.clear();
}

void virtual State::run() {
    int currentTime = SDL_GetTicks();
    int delta = currentTime - prevTime;
    prevTime = currentTime;

    for (auto process: processes) {
        process->update(delta);
    }

    auto iter = std::remove_if(processes.begin(), processes.end(), [](Process::ProcessPtr ptr){ptr->isFinished();});
    processes.erase(iter, processes.end());
}

void State::save(std::ofstream &out) {

}

void State::load(std::ifstream &in) {

}
