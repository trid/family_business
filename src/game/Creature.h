//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CREATURE_H
#define FAMILY_BUSINESS_CREATURE_H


class Creature {
private:
    int x, y;
public:
    int getX() const { return x; }
    void setX(int x) { Creature::x = x; }
    int getY() const { return y; }
    void setY(int y) { Creature::y = y; }
};


#endif //FAMILY_BUSINESS_CREATURE_H
