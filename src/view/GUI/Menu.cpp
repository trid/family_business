//
// Created by TriD on 27.05.2015.
//

#include "Menu.h"

#include <algorithm>

void Menu::draw(SDL_Renderer *renderer) {
    for (auto widget: widgets) {
        widget->draw(renderer);
    }
}

void Menu::draw(SDL_Renderer *renderer, Point &offset) {
    for (auto widget: widgets) {
        widget->draw(renderer, offset + Point(getX(), getY()));
    }
}

void Menu::addWidget(WidgetPtr widget) {
    widgets.push_back(widget);
}

void Menu::removeWidget(WidgetPtr widget) {
    std::remove(begin(widgets), end(widgets), widget);
}

void Menu::clearWidgets() {
    widgets.clear();
}
