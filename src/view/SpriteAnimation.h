//
// Created by TriD on 10.08.2015.
//

#ifndef FAMILY_BUSINESS_SPRITEANIMATION_H
#define FAMILY_BUSINESS_SPRITEANIMATION_H


#include "Animation.h"
#include "Sprite.h"

class SpriteAnimation: public Animation {
    SpritePtr sprite;
    int frameCount;
    int current{0};
    int time; //Time for one frame
    int passed;
public:
    SpriteAnimation(const SpritePtr &sprite, int frameCount, int time) : sprite(sprite), frameCount(frameCount),
                                                                         time(time) { }
    ~SpriteAnimation() {}
    virtual void update(int delta);
    virtual bool isFinished();
    virtual void finalize();
};

#endif //FAMILY_BUSINESS_SPRITEANIMATION_H
