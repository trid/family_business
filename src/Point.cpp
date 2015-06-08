//
// Created by TriD on 27.05.2015.
//

#include "Point.h"

Point operator+(const Point& p1, const Point& p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}
