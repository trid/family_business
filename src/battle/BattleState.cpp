//
// Created by TriD on 24.05.2015.
//

#include "BattleState.h"

void BattleState::onActivate() {
    State::onActivate();
}

void BattleState::run() {
    State::run();
    battle.makeTurn();
}
