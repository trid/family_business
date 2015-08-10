//
// Created by TriD on 10.08.2015.
//

#include "Sprite.h"

void Sprite::draw(SDL_Renderer *renderer) {
    if (!texture) {
        return;
    }

    SDL_Rect rect{position.x, position.y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_Rect src{currentFrame * frameSize.x, 0, frameSize.x, frameSize.y};
    SDL_RenderCopy(renderer, texture, &src, &rect);
}
