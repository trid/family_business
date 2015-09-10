//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "FamilyManager.h"
#include "CharacterManager.h"
#include "Game.h"

using namespace Main;

FamilyManager::FamilyManager() {

}

int FamilyManager::generateFamily() {
    CharacterManager& characterManager = CharacterManager::getInstance();
    int familyId = families.size();

    int fatherId = characterManager.addCharacter(Gender::Male, familyId);
    Character& father = static_cast<Character&>(getCreatureById(fatherId));
    father.addExperience(100);
    father.setAge(parentAgeDistributor(generator));
    int motherId = characterManager.addCharacter(father.getLastName(), Gender::Female, familyId);
    Character& mother = static_cast<Character&>(getCreatureById(motherId));
    mother.setAge(parentAgeDistributor(generator));
    father.setPartnerId(motherId);
    father.setMarried(true);
    mother.setPartnerId(fatherId);
    mother.setMarried(true);
    getCreatureById(motherId).addExperience(100);
    Children children;
    int minAge = father.getAge() > mother.getAge() ? mother.getAge() : father.getAge();
    Distributor childrenAgeDistr{0, minAge - 16
    };
    for (int j = 0; j < 3; j++) {
        int childId = characterManager.addCharacter(father.getLastName(), 1);
        Character& child = static_cast<Character&>(getCreatureById(childId));
        child.setAge(childrenAgeDistr(generator));
        children.push_back(childId);
    }
    families.emplace_back(new Family(familyId, fatherId, motherId, children));
    return familyId;
}

void FamilyManager::save(std::ofstream &out) {
    int count = families.size();
    out.write((char*)&count, sizeof(count));

    for (auto& item: families) {
        item->save(out);
    }
}

void FamilyManager::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        families.emplace_back(new Family(in));
    }
}

int FamilyManager::createFamily(int fatherId, int motherId) {
    std::vector<int> childFree = std::vector<int>();
    families.emplace_back(new Family(families.size(), fatherId, motherId, childFree));
    return families.size() - 1;
}

void FamilyManager::updateDaily() {
    for (auto& item: families) {
        item->updateDaily();
    }
}
