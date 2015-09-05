//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "FamilyManager.h"
#include "CharacterManager.h"
#include "Game.h"

FamilyManager::FamilyManager() {

}

int FamilyManager::generateFamily() {
    CharacterManager& characterManager = CharacterManager::getInstance();
    int familyId = families.size();

    int fatherId = characterManager.addCharacter(Gender::Male, familyId);
    Character& father = static_cast<Character&>(getCreatureById(fatherId));
    father.addExperience(100);
    int motherId = characterManager.addCharacter(father.getLastName(), Gender::Female, familyId);
    Character& mother = static_cast<Character&>(getCreatureById(motherId));
    father.setPartnerId(motherId);
    father.setMarried(true);
    mother.setPartnerId(fatherId);
    mother.setMarried(true);
    getCreatureById(motherId).addExperience(100);
    Children children;
    for (int j = 0; j < 3; j++) {
        children.push_back(characterManager.addCharacter(father.getLastName(), 1));
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
