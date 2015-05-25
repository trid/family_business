//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_WIDGET_H
#define FAMILY_BUSINESS_WIDGET_H


#include <SDL2/SDL.h>

class Widget {
private:
    int x, y, w, h;
public:
    Widget(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }

    virtual void draw(SDL_Renderer* renderer);
};


#endif //FAMILY_BUSINESS_WIDGET_H
