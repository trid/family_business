//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "Family.h"
#include "House.h"

void House::setFamily(const FamilyPtr &family) {
    House::family = family;

    inside.push_back(family->getFather());
    inside.push_back(family->getMother());

    for (auto character: family->getChildren()) {
        inside.push_back(character);
    }
}
