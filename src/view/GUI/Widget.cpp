//
// Created by TriD on 25.05.2015.
//

#include "Widget.h"

bool Widget::onClick(int x, int y, int button) {
    if (!visible) return false;
    if (this->x > x || this->x + w < x) return false;
    if (this->y > y || this->y + h < y) return false;
    return true;
}

void Widget::show() {
    visible = true;
}

void Widget::hide() {
    visible = false;
}

bool Widget::isVisible() {
    return visible;
}
