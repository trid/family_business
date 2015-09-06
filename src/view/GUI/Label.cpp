//
// Created by TriD on 25.07.2015.
//

#include "Label.h"
#include "../Screen.h"
#include "FontsCache.h"

using namespace MEng::View;

Label::Label(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent, const std::string &text) : Widget(x, y, w,
                                                                                                                  h,
                                                                                                                  parent),
                                                                                                           text(text) {
    font = FontsCache::getInstance().getFont("res/fonts/FreeMono.ttf", 14);
    refreshText();
}

void Label::onRedraw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
    SDL_Rect rect = SDL_Rect{0, 0, getWidth(), getHeight()};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}

void Label::setText(const std::string &text) {
    this->text = text;
    refreshText();
}

void Label::refreshText() {
    if (label) {
        SDL_DestroyTexture(label);
    }
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}
