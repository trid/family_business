//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_HOME_H
#define FAMILY_BUSINESS_HOME_H

#include <memory>
#include <vector>

class Family;

using FamilyPtr = std::shared_ptr<Family>;

class House {
private:
    int x, y;
    FamilyPtr family;
public:
    House(int x, int y): x(x), y(y) { }

    int getX() const { return x; }
    void setX(int x) { House::x = x; }
    int getY() const { return y; }
    void setY(int y) { House::y = y; }
    const FamilyPtr &getFamily() const { return family; }
    void setFamily(const FamilyPtr &family) { House::family = family; }
};

using HousePtr = std::shared_ptr<House>;

#endif //FAMILY_BUSINESS_HOME_H
