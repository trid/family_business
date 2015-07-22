//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_HOME_H
#define FAMILY_BUSINESS_HOME_H

#include <memory>
#include <vector>

#include "Side.h"
#include "Family.h"

class Character;

using FamilyPtr = std::shared_ptr<Family>;
using CharacterPtr = std::shared_ptr<Character>;

class House {
private:
    int x, y;
    FamilyPtr family;
    Side side{Side::Player};
    std::vector<CharacterPtr> inside;
public:
    House(int x, int y): x(x), y(y) { }
    House(int x, int y, Side side): x(x), y(y), side(side) { }

    int getX() const { return x; }
    void setX(int x) { House::x = x; }
    int getY() const { return y; }
    void setY(int y) { House::y = y; }
    const FamilyPtr &getFamily() const { return family; }
    void setFamily(const FamilyPtr &family);
    std::vector<CharacterPtr>& getCharacters() { return inside; }
    Side getSide() { return side; }
};

using HousePtr = std::shared_ptr<House>;

#endif //FAMILY_BUSINESS_HOME_H
