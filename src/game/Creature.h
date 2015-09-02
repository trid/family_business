//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_CREATURE_H
#define FAMILY_BUSINESS_CREATURE_H

#include <fstream>
#include <random>

using Generator = std::default_random_engine;
using Distributor = std::uniform_int_distribution<int>;

class Creature {
friend class CreatureManager;
private:
    int id;

    int x, y;
    int hitPoints;
    int attack;
    int speed;
    int defence{0};

    int level{1};
    int experience{0};

    bool alive{true};

    Generator generator;
    Distributor skillUpDistributor{0, 2};
public:
    enum class Type{
        Monster,
        Character
    };

    Creature(int hitPoints, int attack, int speed) : hitPoints(hitPoints), attack(attack), speed(speed) { }
    Creature(std::ifstream& in) { load(in); }
    Creature(const Creature&) = delete;
    Creature& operator=(const Creature&) = delete;

    virtual ~Creature() { }

    virtual Type type() = 0;
    int getX() const { return x; }
    void setX(int x) { Creature::x = x; }
    int getY() const { return y; }
    void setY(int y) { Creature::y = y; }

    int getSpeed() { return speed; }
    int getAttack() { return attack; }
    void setAttack(int attack) { this->attack = attack; }
    int getHitPoints() const { return hitPoints; }
    void setHitPoints(int hitPoints) { Creature::hitPoints = hitPoints; }
    int getDefence() const { return defence; }
    void setDefence(int defence) { Creature::defence = defence; }

    bool isAlive() { return alive; }
    void setAlive(bool alive) { this->alive = alive; }
    void addExperience(int experience);

    int getId() const { return id; }

    virtual void save(std::ofstream& out);
    virtual void load(std::ifstream& in);
};


#endif //FAMILY_BUSINESS_CREATURE_H
