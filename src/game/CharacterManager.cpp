//
// Created by TriD on 25.05.2015.
//

#include "CharacterManager.h"
#include "Character.h"

CharacterPtr CharacterManager::addCharacter() {
    return std::shared_ptr<Character>(new Character("John", "Smith", Gender::Male));
}

CharacterPtr CharacterManager::addCharacter(const string &lastName) {
    return std::shared_ptr<Character>(new Character("John", lastName, Gender::Male));
}

CharacterPtr CharacterManager::addCharacter(const CharacterPtr mother, CharacterPtr father) {
    return std::shared_ptr<Character>(new Character("John", father->getLastName(), Gender::Male));
}

CharacterPtr CharacterManager::addCharacter(const string &lastName, Gender gender) {
    return std::shared_ptr<Character>(new Character("John", lastName, gender));
}
