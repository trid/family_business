//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "View.h"

#include "Screen.h"

void View::draw(SDL_Renderer *renderer) {
    for (auto item: drawables) {
        item->draw(renderer);
    }

    layout.draw(Screen::getInstance().getRenderer());
}

void View::onClick(const Point &point, int button) {
    layout.onClick(point, button);
}
