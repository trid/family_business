//
// Created by TriD on 15.06.2015.
//

#ifndef FAMILY_BUSINESS_MAPVIEW_H
#define FAMILY_BUSINESS_MAPVIEW_H


#include <SDL2/SDL.h>

class MapPresentation {
private:
    SDL_Texture* grass;
    SDL_Texture* house;
public:
    MapPresentation();

    void draw(SDL_Renderer* renderer);
};


#endif //FAMILY_BUSINESS_MAPVIEW_H
