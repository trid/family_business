//
// Created by TriD on 13.06.2015.
//

#include "CharacterButton.h"
#include "../Screen.h"

void CharacterButton::draw(SDL_Renderer *renderer) {
    draw(renderer, Point{});
}

void CharacterButton::draw(SDL_Renderer *renderer, const Point &offset) {
    int realX = getX() + offset.x;
    int realY = getY() + offset.y;
    SDL_Rect rect = SDL_Rect{realX, realY, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    int surfaceW, surfaceH;
    SDL_QueryTexture(label, nullptr, nullptr, &surfaceW, &surfaceH);
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}

CharacterButton::CharacterButton(int x, int y, int w, int h, CharacterPtr character) : Widget(x, y, w, h) {
    font = TTF_OpenFont("res/fonts/FreeMono.ttf", 16);
    const char *c = TTF_GetError();
    SDL_Surface *surface = TTF_RenderText_Solid(font, (character->getName() + " " + character->getLastName()).c_str(),
                                                SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}
