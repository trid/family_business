//
// Created by TriD on 27.05.2015.
//

#include "Point.h"

Point Point::operator+(const Point &p1) {
    return Point(p1.x + this->x, p1.y + this->y);
}
