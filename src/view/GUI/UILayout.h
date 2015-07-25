//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_UILAYOUT_H
#define FAMILY_BUSINESS_UILAYOUT_H

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "../../Point.h"

class Widget;

using WidgetPtr = std::shared_ptr<Widget>;
using Widgets = std::vector<WidgetPtr>;

class UILayout {
private:
    Widgets widgets;
public:
    void draw(SDL_Renderer *renderer);

    void addWidget(WidgetPtr widget);
    void removeWidget(WidgetPtr widget);
    void clearWidgets();

    bool onClick(const Point &point, int button);
};


#endif //FAMILY_BUSINESS_UILAYOUT_H
