//
// Created by TriD on 27.05.2015.
//

#include "Dialog.h"

#include <algorithm>

void Dialog::addWidget(WidgetPtr widget) {
    widgets.push_back(widget);
}

void Dialog::removeWidget(WidgetPtr widget) {
    auto iter = std::remove(begin(widgets), end(widgets), widget);
    widgets.erase(iter, widgets.end());
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

void Dialog::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect{0, 0, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, getTexture());
        }
    }
}

