//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "Family.h"
#include "House.h"
#include "FamilyManager.h"

void House::setFamily(int familyId) {
    House::familyId = familyId;
    Family& family = getFamilyById(familyId);

    inside.push_back(family.getFatherId());
    inside.push_back(family.getMotherId());

    for (auto character: family.getChildren()) {
        inside.push_back(character);
    }
}
