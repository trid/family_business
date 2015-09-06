//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_WIDGET_H
#define FAMILY_BUSINESS_WIDGET_H


#include <memory>
#include <SDL2/SDL.h>
#include "../../Point.h"

using MEng::Point;

class Widget {
private:
    int x, y, w, h;
    bool visible = true;

    SDL_Texture* texture;

    void updateTexture();
    std::shared_ptr<Widget> parent;
protected:
    virtual void onRedraw(SDL_Renderer* renderer) = 0;
    SDL_Texture* getTexture() { return texture; }
public:
    Widget(int x, int y, int w, int h, std::shared_ptr<Widget> parent = nullptr);
    virtual ~Widget() { SDL_DestroyTexture(texture); }

    void draw(SDL_Renderer *renderer, SDL_Texture *parent);
    void centrate();
    void centrateHorizontal();

    int getLeft() { return x; }
    int getTop() { return y; }
    void setLeft(int x) { this->x = x; }
    void setTop(int y) { this->y = y; }

    int getWidth() const { return w; }
    int getHeight() const { return h; }
    int setWidth(int w) { this->w = w; updateTexture(); }
    int setHeight(int h) { this->h = h; updateTexture(); }

    virtual bool onClick(Point point, int button);

    virtual void show();
    virtual void hide();
    virtual bool isVisible();
};


using WidgetPtr = std::shared_ptr<Widget>;

#endif //FAMILY_BUSINESS_WIDGET_H
