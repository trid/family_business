//
// Created by TriD on 13.06.2015.
//

#include "CharacterButton.h"
#include "../../../view/Screen.h"


CharacterButton::CharacterButton(int x, int y, int w, int h, CharacterPtr character, CharacterBtnCallback callback)
        : Widget(x, y, w, h), callback(callback), character(character) {
    font = TTF_OpenFont("res/fonts/FreeMono.ttf", 16);
    SDL_Surface *surface = TTF_RenderText_Solid(font, (character->getName() + " " + character->getLastName()).c_str(),
                                                SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}

bool CharacterButton::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        callback(character);
        return true;
    }
    return false;
}

void CharacterButton::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect = SDL_Rect{0, 0, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    int surfaceW, surfaceH;
    SDL_QueryTexture(label, nullptr, nullptr, &surfaceW, &surfaceH);
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}
