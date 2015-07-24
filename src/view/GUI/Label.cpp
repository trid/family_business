//
// Created by TriD on 25.07.2015.
//

#include "Label.h"
#include "../Screen.h"
#include "FontsCache.h"

Label::Label(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent, const std::string &text) : Widget(x, y, w,
                                                                                                                  h,
                                                                                                                  parent),
                                                                                                           text(text) {
    font = FontsCache::getInstance().getFont("res/fonts/FreeMono.ttf", 16);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(),
                                                SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}

void Label::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect = SDL_Rect{0, 0, getWidth(), getHeight()};
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}