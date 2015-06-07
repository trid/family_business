//
// Created by TriD on 27.05.2015.
//

#ifndef FAMILY_BUSINESS_MENU_H
#define FAMILY_BUSINESS_MENU_H

#include "Widget.h"

#include <memory>
#include <vector>


using Widgets = std::vector<WidgetPtr>;

class Dialog : public Widget {
private:
    Widgets widgets;
public:
    Dialog(int x, int y, int w, int h) : Widget(x, y, w, h) { }

    virtual void draw(SDL_Renderer *renderer);
    virtual void draw(SDL_Renderer *renderer, Point &offset);

    void addWidget(WidgetPtr widget);
    void removeWidget(WidgetPtr widget);
    void clearWidgets();


    virtual bool onClick(int x, int y, int button) override;
};


#endif //FAMILY_BUSINESS_MENU_H
