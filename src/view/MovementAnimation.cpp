//
// Created by TriD on 04.08.2015.
//

#include "MovementAnimation.h"
#include "../MessageManager.h"

void MovementAnimation::update(int delta) {
    passed += delta;
    if (passed < time) {
        Point newPosition;
        newPosition.x = begin.x + distance.x * passed / time;
        newPosition.y = begin.y + distance.y * passed / time;
        image->setPosition(newPosition);
    }
    else {
        image->setPosition(target);
        MessageManager::getInstance().sendMessage("movement_animation_finished", MessageParameters());
    }
}

bool MovementAnimation::isFinished() {
    return passed >= time;
}
