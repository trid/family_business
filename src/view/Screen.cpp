//
// Created by TriD on 24.05.2015.
//

#include "Screen.h"

#include <iostream>
#include <SDL2/SDL_ttf.h>

#include "View.h"
#include "../Application.h"

using std::cout;
using std::endl;

using namespace MEng;

Screen::Screen() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init error" << endl;
        return;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow error" << endl;
        SDL_Quit();
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer error" << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    TTF_Init();
}

void Screen::draw() {
    SDL_RenderClear(renderer);
    Application &application = Application::getInstance();
    if (application.hasState()) {
        application.getCurrentState().getView()->draw(renderer);
    }
    SDL_RenderPresent(renderer);
}
