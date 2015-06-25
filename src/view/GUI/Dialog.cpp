//
// Created by TriD on 27.05.2015.
//

#include "Dialog.h"

#include <algorithm>

void Dialog::draw(SDL_Renderer *renderer) {
    SDL_Rect rect{getLeft(), getTop(), getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, Point{getLeft(), getTop()});
        }
    }
}

void Dialog::draw(SDL_Renderer *renderer, const Point &offset) {
    SDL_Rect rect{getLeft() + offset.x, getTop() + offset.y, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, offset + Point(getLeft(), getTop()));
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

bool Dialog::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        for (auto item: widgets) {
            if (item->onClick(point - Point{getLeft(), getTop()}, button)) return true;
        }
        return true;
    }
    return false;
}
