//
// Created by TriD on 24.05.2015.
//

#include "BattleState.h"
#include "../view/Screen.h"

void BattleState::onActivate() {
    State::onActivate();
    Screen::getInstance().setView(battleView);
}
