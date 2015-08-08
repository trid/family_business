//
// Created by TriD on 04.08.2015.
//

#ifndef FAMILY_BUSINESS_MOVEMENTANIMATION_H
#define FAMILY_BUSINESS_MOVEMENTANIMATION_H


#include "Animation.h"
#include "Image.h"

class MovementAnimation : public Animation {
    ImagePtr image;
    Point begin;
    Point target;
    Point distance;

    int time;
    int passed{0};
public:
    MovementAnimation(const ImagePtr &image, const Point &target, int time) : image(image), begin(image->getPosition()),
                                                                              target(target),
                                                                              distance(target - begin),
                                                                              time(time) { }

    virtual void update(int delta);

    virtual bool isFinished();
};


#endif //FAMILY_BUSINESS_MOVEMENTANIMATION_H
