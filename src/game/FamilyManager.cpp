//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "FamilyManager.h"
#include "Family.h"
#include "CharacterManager.h"

FamilyManager::FamilyManager() {
    CharacterManager& characterManager = CharacterManager::getInstance();

    for (int i = 0; i < 3; i++) {
        CharacterPtr father = characterManager.addCharacter(Gender::Male);
        CharacterPtr mother = characterManager.addCharacter(father->getLastName(), Gender::Female);
        Children children;
        for (int j = 0; j < 3; j++) {
            children.push_back(characterManager.addCharacter(father->getLastName()));
        }
        FamilyPtr family{new Family(father, mother, children)};
        families.push_back(family);
    }
}
