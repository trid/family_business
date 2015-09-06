//
// Created by TriD on 25.05.2015.
//

#include "UILayout.h"

#include <algorithm>

#include "Widget.h"

using namespace MEng::View::GUI;

void UILayout::draw(SDL_Renderer *renderer) {
    for (auto widget: widgets) {
        if (widget->isVisible()) {
            widget->draw(renderer, nullptr);
        }
    }
}

void UILayout::addWidget(WidgetPtr widget) {
    widgets.push_back(widget);
}

void UILayout::removeWidget(WidgetPtr widget) {
    std::remove(begin(widgets), end(widgets), widget);
}

void UILayout::clearWidgets() {
    widgets.clear();
}

bool UILayout::onClick(const Point &point, int button) {
    for (auto item: widgets) {
        if (item->onClick(point, button)){
            return true;
        }
    }
    return false;
}
