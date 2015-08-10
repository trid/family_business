//
// Created by dmitry-khovyakov on 5/25/15.
//

#include <iostream>
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

void View::update(int timeDelta) {
    for (auto animation: animations) {
        animation->update(timeDelta);
    }

    std::for_each(animations.begin(), animations.end(), [](AnimationPtr animationPtr) { if (animationPtr->isFinished()) animationPtr->finalize(); });
    auto iter = std::remove_if(animations.begin(), animations.end(), [](AnimationPtr animationPtr){ return animationPtr->isFinished();});
    animations.erase(iter, animations.end());
}
