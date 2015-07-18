//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_BATTLESTATE_H
#define FAMILY_BUSINESS_BATTLESTATE_H


#include "../State.h"
#include "../view/BattleView.h"
#include "../game/Game.h"


class BattleState : public State {
private:
    Battle battle;
public:
    BattleState(PartyPtr first, PartyPtr second) : battle(first, second) {
        setView(ViewPtr(new BattleView(battle)));
    }

    virtual void onActivate() override;
    virtual void onClick(const Point &point, int button) override;

    virtual void run() override;
};


#endif //FAMILY_BUSINESS_BATTLESTATE_H
