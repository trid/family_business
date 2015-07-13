//
// Created by TriD on 25.05.2015.
//

#include "Widget.h"
#include "../Screen.h"

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

void Widget::draw(SDL_Renderer *renderer, SDL_Texture *parent) {
    SDL_SetRenderTarget(renderer, texture);
    onRedraw(renderer);
    SDL_SetRenderTarget(renderer, parent);
    SDL_Rect dst{x, y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

Widget::Widget(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
    texture = SDL_CreateTexture(Screen::getInstance().getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);
}

void Widget::updateTexture() {
    {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
        texture = SDL_CreateTexture(Screen::getInstance().getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);
    }
}
