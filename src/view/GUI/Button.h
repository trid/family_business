//
// Created by TriD on 22.06.2015.
//

#ifndef FAMILY_BUSINESS_BUTTON_H
#define FAMILY_BUSINESS_BUTTON_H

#include <functional>
#include <SDL2/SDL_ttf.h>
#include "Widget.h"

using Callback = std::function<void()>;

class Button : public Widget {
private:
    Callback callback;
    std::string text;
    TTF_Font* font;
    SDL_Texture* label;
protected:
    virtual void onRedraw(SDL_Renderer *renderer);
public:
    Button(int x, int y, int w, int h, std::string text, Callback callback);

    virtual bool onClick(Point point, int button) override;
};


#endif //FAMILY_BUSINESS_BUTTON_H
