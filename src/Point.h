//
// Created by TriD on 27.05.2015.
//

#ifndef FAMILY_BUSINESS_POINT_H
#define FAMILY_BUSINESS_POINT_H

namespace MEng {

    class Point {
    public:
        int x, y;

        Point() = default;

        Point(int x, int y) : x(x), y(y) { }
    };

    inline Point operator+(const Point &p1, const Point &p2) {
        return Point{p1.x + p2.x, p1.y + p2.y};
    }

    inline Point operator-(const Point &p1, const Point &p2) {
        return Point{p1.x - p2.x, p1.y - p2.y};
    }

    inline bool operator==(const Point &p1, const Point &p2) {
        return p1.x == p2.x && p1.y == p2.y;
    }

}

#endif //FAMILY_BUSINESS_POINT_H
