//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_FAMILYMANAGER_H
#define FAMILY_BUSINESS_FAMILYMANAGER_H

#include <fstream>

#include "Family.h"

namespace Main {

    using FamilyPtr = std::unique_ptr<Main::Family>;
    using Families = std::vector<FamilyPtr>;

    class FamilyManager {
    private:
        FamilyManager();

        Families families;

        Main::Generator generator;
        Main::Distributor parentAgeDistributor{16 * 12 * 30, 50 * 12 * 30};
    public:
        static FamilyManager &getInstance() {
            static FamilyManager instance;
            return instance;
        }

        const Families &getFamilies() { return families; }

        Main::Family &getFamilyById(int id) { return *families[id]; }

        int generateFamily();

        void clear() { families.clear(); }

        int createFamily(int fatherId, int motherId);

        void updateDaily();

        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

    inline Main::Family &getFamilyById(int id) {
        return FamilyManager::getInstance().getFamilyById(id);
    }

}
#endif //FAMILY_BUSINESS_FAMILYMANAGER_H
