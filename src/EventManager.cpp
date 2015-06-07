//
// Created by TriD on 25.05.2015.
//

#include <SDL2/SDL.h>

#include "EventManager.h"
#include "Application.h"


void EventManager::process() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Application::getInstance().finish();
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            Application::getInstance().getCurrentState().onClick(Point{event.button.x, event.button.y}, event.button.button);
        }
    }
}
