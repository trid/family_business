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
}

bool MovementAnimation::isFinished() {
    return passed >= time;
}

void MovementAnimation::finalize() {
    image->setPosition(target);
    MessageParameters parameters = MessageParameters();
    MessageManager::getInstance().enqueuMessage("movement_animation_finished", parameters);
}
