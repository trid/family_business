//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_FAMILY_H
#define FAMILY_BUSINESS_FAMILY_H

#include <memory>
#include <vector>

class Character;

using CharacterPtr = std::shared_ptr<Character>;
using Children = std::vector<CharacterPtr>;

class Family {
    CharacterPtr father;
    CharacterPtr mother;
    Children children;
};


#endif //FAMILY_BUSINESS_FAMILY_H
