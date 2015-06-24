//
// Created by TriD on 22.06.2015.
//

#include "Button.h"

bool Button::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        callback();
        return true;
    }
    return false;
}
