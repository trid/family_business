//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "FamilyManager.h"
#include "CharacterManager.h"
#include "Game.h"

FamilyManager::FamilyManager() {
    CharacterManager& characterManager = CharacterManager::getInstance();

    for (int i = 0; i < 3; i++) {
        int fatherId = characterManager.addCharacter(Gender::Male, i);
        Character& father = static_cast<Character&>(getCreatureById(fatherId));
        father.addExperience(100);
        int motherId = characterManager.addCharacter(father.getLastName(), Gender::Female, i);
        getCreatureById(motherId).addExperience(100);
        Children children;
        for (int j = 0; j < 3; j++) {
            children.push_back(characterManager.addCharacter(father.getLastName(), 1));
        }
        families.emplace_back(new Family(i, fatherId, motherId, children));
    }
}
