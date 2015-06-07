//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_WIDGET_H
#define FAMILY_BUSINESS_WIDGET_H


#include <memory>
#include <SDL2/SDL.h>
#include "../../Point.h"

class Widget {
private:
    int x, y, w, h;
    bool visible = true;
public:
    Widget(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void draw(SDL_Renderer* renderer, const Point& offset) = 0;

    int getX() { return x; }
    int getY() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    virtual bool onClick(int x, int y, int button);

    virtual void show();
    virtual void hide();
    virtual bool isVisible();
};


using WidgetPtr = std::shared_ptr<Widget>;

#endif //FAMILY_BUSINESS_WIDGET_H
