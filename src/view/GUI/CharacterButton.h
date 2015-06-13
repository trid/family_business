//
// Created by TriD on 13.06.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERBUTTON_H
#define FAMILY_BUSINESS_CHARACTERBUTTON_H


#include <SDL2/SDL_ttf.h>
#include "Widget.h"
#include "../../game/CharacterManager.h"

class CharacterButton: public Widget {
private:
    SDL_Texture* label;
    TTF_Font* font;
public:
    CharacterButton(int x, int y, int w, int h, CharacterPtr character);

    virtual void draw(SDL_Renderer *renderer);
    virtual void draw(SDL_Renderer *renderer, const Point &offset);
};


#endif //FAMILY_BUSINESS_CHARACTERBUTTON_H
