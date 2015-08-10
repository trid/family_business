//
// Created by TriD on 10.08.2015.
//

#ifndef FAMILY_BUSINESS_SPRITE_H
#define FAMILY_BUSINESS_SPRITE_H

#include <SDL2/SDL.h>

#include "Drawable.h"
#include "../Point.h"

class Sprite : public Drawable {
private:
    Point frameSize;
    int currentFrame{0};

    Point position;

    SDL_Texture *texture;
public:
    Sprite(const Point &frameSize, const Point &position, SDL_Texture *texture) : frameSize(frameSize),
                                                                                  position(position),
                                                                                  texture(texture) { }
    void nextFrame() { ++currentFrame; }
    void resetFrame() { currentFrame = 0; }
    virtual void draw(SDL_Renderer *renderer) override;

    void setPosition(Point position) { this->position = position; }
};

using SpritePtr = std::shared_ptr<Sprite>;

#endif //FAMILY_BUSINESS_SPRITE_H
