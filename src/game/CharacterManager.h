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
public:
    static CharacterManager& getInstance(){
        static CharacterManager instance;
        return instance;
    }

    int addCharacter(Gender gender, FamilyPtr family);
    int addCharacter(const string &lastName, FamilyPtr family);
    int addCharacter(const CharacterPtr mother, CharacterPtr father);
    int addCharacter(const string &lastName, Gender gender, FamilyPtr family);
};


#endif //FAMILY_BUSINESS_CHARACTERMANAGER_H
