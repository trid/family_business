//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BUTTON_H
#define FAMILY_BUSINESS_BUTTON_H

#include <functional>
#include "Widget.h"

using Callback = std::function<void()>;

class Button: public Widget {
private:
    Callback callback;

public:
    Button(int x, int y, int w, int h, Callback callback) : Widget(x, y, w, h), callback(callback) { }

    virtual bool onClick(int x, int y, int button) override;
};


#endif //FAMILY_BUSINESS_BUTTON_H
