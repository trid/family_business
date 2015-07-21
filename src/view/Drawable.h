//
// Created by TriD on 22.07.2015.
//

#ifndef FAMILY_BUSINESS_DRAWABLE_H
#define FAMILY_BUSINESS_DRAWABLE_H


#include <SDL2/SDL.h>

class Drawable {
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
};


#endif //FAMILY_BUSINESS_DRAWABLE_H
