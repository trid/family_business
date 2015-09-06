//
// Created by TriD on 25.05.2015.
//

#include <SDL2/SDL.h>

#include "EventManager.h"
#include "Application.h"

using namespace MEng;

void EventManager::process() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Application::getInstance().finish();
                break;
            case SDL_MOUSEBUTTONUP:
                Application::getInstance().getCurrentState().onClick(Point{event.button.x, event.button.y}, event.button.button);
                break;
            case SDL_KEYUP:
                Application::getInstance().getCurrentState().onKeyUp(event.key.keysym.sym);
                break;
            case SDL_KEYDOWN:
                Application::getInstance().getCurrentState().onKeyDown(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}
