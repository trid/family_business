//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "FamilyManager.h"
#include "CharacterManager.h"
#include "Game.h"

FamilyManager::FamilyManager() {
    CharacterManager& characterManager = CharacterManager::getInstance();

    for (int i = 0; i < 3; i++) {
        CharacterPtr father = characterManager.addCharacter(Gender::Male, (std::shared_ptr<Family>()));
        CharacterPtr mother = characterManager.addCharacter(father->getLastName(), Gender::Female,
                                                            (std::shared_ptr<Family>()));
        Children children;
        for (int j = 0; j < 3; j++) {
            children.push_back(characterManager.addCharacter(father->getLastName(), (std::shared_ptr<Family>())));
        }
        FamilyPtr family{new Family(father, mother, children)};
        families.push_back(family);
    }
}
