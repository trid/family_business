//
// Created by TriD on 27.05.2015.
//

#include "Dialog.h"

#include <algorithm>

void Dialog::draw(SDL_Renderer *renderer) {
    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, Point{getX(), getY()});
        }
    }
}

void Dialog::draw(SDL_Renderer *renderer, const Point &offset) {
    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, offset + Point(getX(), getY()));
        }
    }
}

void Dialog::addWidget(WidgetPtr widget) {
    widgets.push_back(widget);
}

void Dialog::removeWidget(WidgetPtr widget) {
    std::remove(begin(widgets), end(widgets), widget);
}

void Dialog::clearWidgets() {
    widgets.clear();
}

bool Dialog::onClick(int x, int y, int button) {
    if (Widget::onClick(x, y, button)) {
        for (auto item: widgets) {
            if (item->onClick(x - getX(), y - getY(), button)) return true;
        }
        return true;
    }
    return false;
}
