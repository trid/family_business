//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_MAPSTATE_H
#define FAMILY_BUSINESS_MAPSTATE_H

#include <fstream>

#include "../State.h"
#include "view/MainView.h"
#include "view/GUI/CharacterPanel.h"
#include "Movement.h"

class MainState : public State {
    unsigned int lastTime{SDL_GetTicks()};
    std::vector<MovementPtr> movement;

    class CharacterWinListener: public MessageListener {
    public:
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };

    class CharacterMovedListener: public MessageListener {
    public:
        virtual void onMessage(const MessageParameters &messageParameters);
    };
public:
    MainState();

    virtual void onClick(const Point &point, int button) override;
    virtual void onKeyDown(int keyCode) override;
    virtual void onKeyUp(int keyCode) override;
    virtual void onActivate() override;
    virtual void onPop() override;

    virtual void run() override;

    void takeMercenary();

    void battleMonsters();

    void save(std::ofstream &out);
};


#endif //FAMILY_BUSINESS_MAPSTATE_H
