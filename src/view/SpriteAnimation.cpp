//
// Created by TriD on 10.08.2015.
//

#include "SpriteAnimation.h"
#include "../MessageManager.h"

void SpriteAnimation::update(int delta) {
    passed += delta;
    if (passed >= time) {
        ++current;
        sprite->nextFrame();
        passed -= time;
    }
}

bool SpriteAnimation::isFinished() {
    return current > frameCount;
}

void SpriteAnimation::finalize() {
    MessageParameters parameters = MessageParameters();
    MessageManager::getInstance().enqueuMessage("sprite_animation_finished", parameters);
}
