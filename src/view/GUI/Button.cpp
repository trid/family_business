//
// Created by TriD on 22.06.2015.
//

#include "Button.h"

bool Button::onClick(int x, int y, int button) {
    if (Widget::onClick(x, y, button)) {
        callback();
        return true;
    }
    return false;
}
