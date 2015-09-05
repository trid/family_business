//
// Created by TriD on 25.05.2015.
//

#include "CharacterManager.h"
#include "Character.h"
#include "CreatureManager.h"
#include "AbstractAI.h"
#include "CharacterAI.h"

#include <fstream>
#include <ctime>

int CharacterManager::addCharacter(Gender gender, int familyId) {
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    std::unique_ptr<Creature> character = std::unique_ptr<Character>(
            new Character(name, lastNames[lastNamesRNG(generator)], gender,
                          familyId));
    int characterId = CreatureManager::getInstance().registerCreature(character);
    AbstractAIPtr abstractAIPtr{new CharacterAI(characterId)};
    return characterId;
}

int CharacterManager::addCharacter(const string &lastName, int familyId) {
    Gender gender = genderRNG(generator) ? Gender::Male : Gender::Female;
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    std::unique_ptr<Creature> character = std::unique_ptr<Character>(new Character(name, lastName, gender, familyId));
    int characterId = CreatureManager::getInstance().registerCreature(character);
    AbstractAIPtr abstractAIPtr{new CharacterAI(characterId)};
    return characterId;
}

int CharacterManager::addCharacter(int motherId, int fatherId) {
    Gender gender = genderRNG(generator) ? Gender::Male : Gender::Female;
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    Character& father = static_cast<Character&>(getCreatureById(fatherId));
    std::unique_ptr<Creature> character = std::unique_ptr<Character>(new Character(name, father.getLastName(), gender,
                                                                                   father.getFamilyId()));
    int characterId = CreatureManager::getInstance().registerCreature(character);
    AbstractAIPtr abstractAIPtr{new CharacterAI(characterId)};
    return characterId;
}

int CharacterManager::addCharacter(const string &lastName, Gender gender, int family) {
    std::string &name =
            gender == Gender::Male ? maleNames[maleNamesRNG(generator)] : femaleNames[femaleNamesRNG(generator)];
    std::unique_ptr<Creature> character = std::unique_ptr<Character>(new Character(name, lastName, gender, family));
    int characterId = CreatureManager::getInstance().registerCreature(character);
    AbstractAIPtr abstractAIPtr{new CharacterAI(characterId)};
    return characterId;
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
