//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_BATTLESTATE_H
#define FAMILY_BUSINESS_BATTLESTATE_H


#include "../State.h"
#include "../game/Tile.h"
#include "../view/BattleView.h"
#include "../game/Game.h"


class BattleState : public State {
private:
    Battle battle;
    ViewPtr battleView;
public:
    BattleState(CreaturePtr creature) : battle(Game::getInstance().getPlayerCharacter(), creature),
                                        battleView(new BattleView(battle)) { }

    virtual void onActivate() override;
};


#endif //FAMILY_BUSINESS_BATTLESTATE_H
