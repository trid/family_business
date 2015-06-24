//
// Created by TriD on 25.05.2015.
//

#include "Widget.h"

bool Widget::onClick(Point point, int button) {
    if (!visible) return false;
    if (this->x > point.x || this->x + w < point.x) return false;
    if (this->y > point.y || this->y + h < point.y) return false;
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
