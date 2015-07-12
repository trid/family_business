//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CREATURE_H
#define FAMILY_BUSINESS_CREATURE_H


class Creature {
private:
    int x, y;
    int hitPoints;
    int attack;
    int speed;
public:
    enum class Type{
        Monster,
        Character
    };

    Creature(int hitPoints, int attack, int speed) : hitPoints(hitPoints), attack(attack), speed(speed) { }
    virtual ~Creature() { }

    virtual Type type() = 0;
    int getX() const { return x; }
    void setX(int x) { Creature::x = x; }
    int getY() const { return y; }
    void setY(int y) { Creature::y = y; }

    int getSpeed() { return speed; }
    int getAttack() { return attack; }
    int getHitPoints() const { return hitPoints; }
    void setHitPoints(int hitPoints) { Creature::hitPoints = hitPoints; }
};


#endif //FAMILY_BUSINESS_CREATURE_H
