//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERMANAGER_H
#define FAMILY_BUSINESS_CHARACTERMANAGER_H


#include <memory>
#include <random>
#include <string>
#include <vector>
#include "Character.h"

using std::string;

class Character;

using CharacterPtr = std::shared_ptr<Character>;
using Characters = std::vector<CharacterPtr>;

using Generator = std::default_random_engine;
using Distributor = std::uniform_int_distribution<int>;


class CharacterManager {
private:
    CharacterManager();

    std::vector<string> maleNames;
    std::vector<string> femaleNames;
    std::vector<string> lastNames;

    Generator generator;
    Distributor maleNamesRNG;
    Distributor femaleNamesRNG;
    Distributor lastNamesRNG;
    Distributor genderRNG;

    Characters characters;
public:
    static CharacterManager& getInstance(){
        static CharacterManager instance;
        return instance;
    }

    CharacterPtr addCharacter(Gender gender, FamilyPtr family);
    CharacterPtr addCharacter(const string &lastName, FamilyPtr family);
    CharacterPtr addCharacter(const CharacterPtr mother, CharacterPtr father);
    CharacterPtr addCharacter(const string &lastName, Gender gender, FamilyPtr family);

    Character& getCharacterById(int id) { return *characters[id]; }
};


#endif //FAMILY_BUSINESS_CHARACTERMANAGER_H
