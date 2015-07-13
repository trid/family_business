//
// Created by TriD on 13.06.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERBUTTON_H
#define FAMILY_BUSINESS_CHARACTERBUTTON_H


#include <functional>
#include <SDL2/SDL_ttf.h>
#include "../../../view/GUI/Widget.h"
#include "../../CharacterManager.h"

using CharacterBtnCallback = std::function<void(CharacterPtr)>;

class CharacterButton: public Widget {
private:
    SDL_Texture* label;
    TTF_Font* font;

    CharacterPtr character;
    CharacterBtnCallback callback;
protected:
    virtual void onRedraw(SDL_Renderer *renderer) override;
public:
    CharacterButton(int x, int y, int w, int h, CharacterPtr character, CharacterBtnCallback callback);

    virtual bool onClick(Point point, int button) override;
};


#endif //FAMILY_BUSINESS_CHARACTERBUTTON_H
