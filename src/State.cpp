//
// Created by TriD on 24.05.2015.
//

#include <algorithm>

#include "State.h"

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
