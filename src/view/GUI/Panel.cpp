//
// Created by TriD on 01.08.2015.
//

#include <algorithm>

#include "Panel.h"

void Panel::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect{0, 0, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, getTexture());
        }
    }
}

void Panel::addWidget(WidgetPtr widget) {
    widgets.push_back(widget);
}

void Panel::removeWidget(WidgetPtr widget) {
    auto iter = std::remove(begin(widgets), end(widgets), widget);
    widgets.erase(iter, widgets.end());
}

void Panel::clearWidgets() {
    widgets.clear();
}

bool Panel::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        for (auto item: widgets) {
            if (item->onClick(point - Point{getLeft(), getTop()}, button)) return true;
        }
        return true;
    }
    return false;
}
