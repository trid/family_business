//
// Created by TriD on 04.08.2015.
//

#include "MovementAnimation.h"

void MovementAnimation::update(int delta) {
    if (passed < time) {
        passed += delta;
        Point newPosition;
        newPosition.x = begin.x + distance.x * passed / time;
        newPosition.y = begin.y + distance.y * passed / time;
        image->setPosition(newPosition);
    }
}

bool MovementAnimation::isFinished() {
    return passed >= time;
}
