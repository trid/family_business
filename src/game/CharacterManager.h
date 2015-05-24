//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERMANAGER_H
#define FAMILY_BUSINESS_CHARACTERMANAGER_H


#include <memory>
#include <string>
#include <vector>
#include "Character.h"

using std::string;

class Character;

using CharacterPtr = std::shared_ptr<Character>;
using Characters = std::vector<CharacterPtr>;


class CharacterManager {
private:
    CharacterManager() {};
public:
    static CharacterManager& getInstance(){
        static CharacterManager instance;
        return instance;
    }

    CharacterPtr addCharacter();
    CharacterPtr addCharacter(const string& lastName);
    CharacterPtr addCharacter(const CharacterPtr mother, CharacterPtr father);
    CharacterPtr addCharacter(const string& lastName, Gender gender);
};


#endif //FAMILY_BUSINESS_CHARACTERMANAGER_H
