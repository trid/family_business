//
// Created by TriD on 21.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLEVIEW_H
#define FAMILY_BUSINESS_BATTLEVIEW_H


#include "View.h"
#include "../battle/Battle.h"

class BattleView: public View {
    Battle& battle;

    SDL_Texture* grass;
    SDL_Texture* character;
    SDL_Texture* monster;
    int dx, dy;
public:
    BattleView(Battle& battle);

    virtual void draw() override;
};


#endif //FAMILY_BUSINESS_BATTLEVIEW_H
