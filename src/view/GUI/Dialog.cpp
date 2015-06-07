//
// Created by TriD on 27.05.2015.
//

#include "Dialog.h"

#include <algorithm>

void Dialog::draw(SDL_Renderer *renderer) {
    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer);
        }
    }
}

void Dialog::draw(SDL_Renderer *renderer, Point &offset) {
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
            item->onClick(x, y, button);
        }
    }
}
