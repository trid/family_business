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
