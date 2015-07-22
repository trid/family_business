//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_MAPSTATE_H
#define FAMILY_BUSINESS_MAPSTATE_H


#include "../State.h"
#include "view/MainView.h"

class MainState : public State {
    unsigned int lastTime{SDL_GetTicks()};
public:
    MainState();

    virtual void onClick(const Point &point, int button) override;
    virtual void onKeyDown(int keyCode) override;
    virtual void onKeyUp(int keyCode) override;
    virtual void onActivate() override;

    virtual void run() override;

    void takeMercenary();

    void battleMonsters();
};


#endif //FAMILY_BUSINESS_MAPSTATE_H
