//
// Created by TriD on 02.08.2015.
//

#include "Movement.h"
#include "../MessageManager.h"

void Movement::update(int delta) {
    time += delta;

    if (time >= 500) {
        party->setMoving(false);
        MessageParameters parameters;
        parameters.setParameter("x", target.x);
        parameters.setParameter("y", target.y);
        MessageManager::getInstance().sendMessage("character_moved", parameters);
    }
}
