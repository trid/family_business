//
// Created by TriD on 22.06.2015.
//

#include "Button.h"
#include "../Screen.h"
#include "FontsCache.h"

bool Button::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        callback();
        return true;
    }
    return false;
}

void Button::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect = SDL_Rect{0, 0, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}

Button::Button(int x, int y, int w, int h, const std::string &text, Callback callback) : Widget(x, y, w, h),
                                                                                  callback(callback) {
    font = FontsCache::getInstance().getFont("res/fonts/FreeMono.ttf", 16);
    setText(text);
}

void Button::setText(const std::string &text) {
    this->text = text;

    if (label) {
        SDL_DestroyTexture(label);
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}
