//
// Created by TriD on 25.07.2015.
//

#ifndef FAMILY_BUSINESS_LABEL_H
#define FAMILY_BUSINESS_LABEL_H


#include <SDL2/SDL_ttf.h>
#include "Widget.h"

class Label : Widget {
private:
    std::string text;
    SDL_Texture* label;
    TTF_Font* font;
public:
    Label(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent, const std::string &text);

private:
    virtual void onRedraw(SDL_Renderer *renderer);
};


#endif //FAMILY_BUSINESS_LABEL_H
