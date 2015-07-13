//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_VILLAGE_H
#define FAMILY_BUSINESS_VILLAGE_H


#include "../Point.h"

class Village {
    Point center;

public:
    Village() {}

    const Point &getCenter() const { return center; }
    void setCenter(const Point &center) { Village::center = center; }
};


#endif //FAMILY_BUSINESS_VILLAGE_H
