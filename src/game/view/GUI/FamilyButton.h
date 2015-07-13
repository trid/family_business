//
// Created by TriD on 08.06.2015.
//

#ifndef FAMILY_BUSINESS_FAMILYBUTTON_H
#define FAMILY_BUSINESS_FAMILYBUTTON_H

#include <functional>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../../view/GUI/Widget.h"

class Family;
class MainView;

using FamilyPtr = std::shared_ptr<Family>;
using Callback = std::function<void(FamilyPtr)>;

class FamilyButton: public Widget {
private:
    FamilyPtr family;
    Callback callback;

    SDL_Texture* label;
    TTF_Font* font;
protected:
    virtual void onRedraw(SDL_Renderer *renderer) override;
public:
    FamilyButton(int x, int y, int w, int h, const FamilyPtr &family, Callback callback);
    virtual ~FamilyButton();

    virtual bool onClick(Point point, int button) override;
};


#endif //FAMILY_BUSINESS_FAMILYBUTTON_H
