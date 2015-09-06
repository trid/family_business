//
// Created by TriD on 05.08.2015.
//

#ifndef FAMILY_BUSINESS_MOVEMAPANIMATION_H
#define FAMILY_BUSINESS_MOVEMAPANIMATION_H


#include "../../view/Animation.h"

class MoveMapAnimation: public MEng::View::Animation {

public:
    virtual void update(int delta);

    virtual bool isFinished();
};


#endif //FAMILY_BUSINESS_MOVEMAPANIMATION_H
