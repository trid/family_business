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
    SDL_Color backgroundColor{0, 0, 0, 0};
public:
    Dialog(int x, int y, int w, int h) : Widget(x, y, w, h) { }

    virtual void draw(SDL_Renderer *renderer) override;
    virtual void draw(SDL_Renderer *renderer, const Point &offset) override;

    void addWidget(WidgetPtr widget);
    void removeWidget(WidgetPtr widget);
    void clearWidgets();

    SDL_Color getBgColor() const { return backgroundColor; }
    void setBgColor(SDL_Color color) { Dialog::backgroundColor = color; }

    virtual bool onClick(int x, int y, int button) override;
};


#endif //FAMILY_BUSINESS_MENU_H
