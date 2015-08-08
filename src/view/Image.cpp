//
// Created by TriD on 04.08.2015.
//

#include "Image.h"

void Image::draw(SDL_Renderer *renderer) {
    if (!texture) {
        return;
    }

    SDL_Rect rect{position.x, position.y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
