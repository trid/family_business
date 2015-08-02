//
// Created by TriD on 25.05.2015.
//

#include "CharacterManager.h"
#include "Character.h"

#include <fstream>
#include <ctime>

CharacterPtr CharacterManager::addCharacter(Gender gender, FamilyPtr family) {
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    const std::shared_ptr<Character> character = std::shared_ptr<Character>(
            new Character(name, lastNames[lastNamesRNG(generator)], gender,
                          family));
    characters.push_back(character);
    return character;
}

CharacterPtr CharacterManager::addCharacter(const string &lastName, FamilyPtr family) {
    Gender gender = genderRNG(generator) ? Gender::Male : Gender::Female;
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    const std::shared_ptr<Character> character = std::shared_ptr<Character>(new Character(name, lastName, gender, family));
    characters.push_back(character);
    return character;
}

CharacterPtr CharacterManager::addCharacter(const CharacterPtr mother, CharacterPtr father) {
    Gender gender = genderRNG(generator) ? Gender::Male : Gender::Female;
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    const std::shared_ptr<Character> character = std::shared_ptr<Character>(new Character(name, father->getLastName(), gender, father->getFamily()));
    characters.push_back(character);
    return character;
}

CharacterPtr CharacterManager::addCharacter(const string &lastName, Gender gender, FamilyPtr family) {
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    const std::shared_ptr<Character> character = std::shared_ptr<Character>(
                new Character(name, lastName, gender, family));
    characters.push_back(character);
    return character;
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

    maleNamesRNG = Distributor(0, maleNames.size() - 1);
    femaleNamesRNG = Distributor(0, femaleNames.size() - 1);
    lastNamesRNG = Distributor(0, lastNames.size() - 1);
    genderRNG = Distributor(0, 1);
    generator.seed(std::time(0));
}
