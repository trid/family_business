//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "Family.h"
#include "Building.h"
#include "FamilyManager.h"

using namespace Main;

void Building::setFamily(int familyId) {
    Building::familyId = familyId;
    Family& family = getFamilyById(familyId);

    inside.push_back(family.getFatherId());
    inside.push_back(family.getMotherId());

    for (auto character: family.getChildren()) {
        inside.push_back(character);
    }
}

void Building::save(std::ofstream &out) {
    out.write(reinterpret_cast<char*>(&id), sizeof(id));
    out.write(reinterpret_cast<char*>(&x), sizeof(x));
    out.write(reinterpret_cast<char*>(&y), sizeof(y));
    out.write(reinterpret_cast<char*>(&familyId), sizeof(familyId));
    out.write(reinterpret_cast<char*>(&type), sizeof(type));

    int count = inside.size();
    out.write(reinterpret_cast<char*>(&inside), sizeof(inside));

    for (int i: inside) {
        out.write(reinterpret_cast<char*>(&i), sizeof(i));
    }
}

void Building::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    in.read(reinterpret_cast<char*>(&y), sizeof(y));
    in.read(reinterpret_cast<char*>(&familyId), sizeof(familyId));
    in.read(reinterpret_cast<char*>(&type), sizeof(type));

    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    //Read characters that are inside house now
    for (int i = 0; i < count; i++) {
        int t{0};
        in.read(reinterpret_cast<char*>(&t), sizeof(t));
        inside.push_back(t);
    }
}
