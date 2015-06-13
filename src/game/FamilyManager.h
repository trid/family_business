//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_FAMILYMANAGER_H
#define FAMILY_BUSINESS_FAMILYMANAGER_H

#include "Family.h"

using Families = std::vector<FamilyPtr>;

class FamilyManager {
private:
    FamilyManager();

    Families families;
public:
    static FamilyManager& getInstance() {
        static FamilyManager instance;
        return instance;
    }

    const Families& getFamilies() { return families; }
};


#endif //FAMILY_BUSINESS_FAMILYMANAGER_H
