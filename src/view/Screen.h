//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_SCREEN_H
#define FAMILY_BUSINESS_SCREEN_H


#include <SDL2/SDL.h>
#include <memory>


class View;


using ViewPtr = std::shared_ptr<View>;


class Screen {
private:
    int width = 800;
    int height = 600;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Screen();
    ViewPtr view;
public:
    static Screen& getInstance() {
        static Screen instance;
        return instance;
    }

    void draw();
    void setView(ViewPtr view) { this->view = view; }
    SDL_Renderer* getRenderer() { return renderer; }
};


#endif //FAMILY_BUSINESS_SCREEN_H
