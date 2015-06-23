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
    SDL_Texture* character;
    SDL_Texture* monster;

    int dx{}, dy{};
public:
    MapPresentation();

    void draw(SDL_Renderer* renderer);
    void update(int timeDelta);

    void setDeltas(int dx, int dy) { this->dx = dx; this->dy = dy; }
};


#endif //FAMILY_BUSINESS_MAPVIEW_H
