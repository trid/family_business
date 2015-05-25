//
// Created by TriD on 25.05.2015.
//

#include "CharacterManager.h"
#include "Character.h"

#include <fstream>

CharacterPtr CharacterManager::addCharacter(Gender gender) {
    return std::shared_ptr<Character>(
            new Character(maleNames[maleNamesRNG(generator)], lastNames[lastNamesRNG(generator)], gender));
}

CharacterPtr CharacterManager::addCharacter(const string &lastName) {
    return std::shared_ptr<Character>(new Character(maleNames[maleNamesRNG(generator)], lastName,
                                                    genderRNG(generator) ? Gender::Male : Gender::Female));
}

CharacterPtr CharacterManager::addCharacter(const CharacterPtr mother, CharacterPtr father) {
    return std::shared_ptr<Character>(new Character(maleNames[maleNamesRNG(generator)], father->getLastName(),
                                                    genderRNG(generator) ? Gender::Male : Gender::Female));
}

CharacterPtr CharacterManager::addCharacter(const string &lastName, Gender gender) {
    return std::shared_ptr<Character>(new Character(maleNames[maleNamesRNG(generator)], lastName, gender));
}

CharacterManager::CharacterManager() {
    std::ifstream maleNamesFile("res/characters/male_names.txt");
    std::ifstream femaleNamesFile("res/characters/female_names.txt");
    std::ifstream lastNamesFile("res/characters/last_names.txt");

    while (!maleNamesFile.eof()) {
        string name;
        std::getline(maleNamesFile, name);
        maleNames.push_back(name);
    }

    while (!femaleNamesFile.eof()) {
        string name;
        std::getline(femaleNamesFile, name);
        femaleNames.push_back(name);
    }

    while (!lastNamesFile.eof()) {
        string name;
        std::getline(lastNamesFile, name);
        lastNames.push_back(name);
    }

    maleNamesRNG = Distributor(0, maleNames.size());
    femaleNamesRNG = Distributor(0, femaleNames.size());
    lastNamesRNG = Distributor(0, lastNames.size());
    genderRNG = Distributor(0, 1);
}
