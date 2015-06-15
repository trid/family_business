//
// Created by TriD on 14.06.2015.
//

#ifndef FAMILY_BUSINESS_GAME_H
#define FAMILY_BUSINESS_GAME_H


#include "CharacterManager.h"
#include "GameMap.h"

class Game {
private:
    CharacterPtr playerCharacter;
    HousePtr housePtr;
    GameMap gameMap;

    Game(){};
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    GameMap& getMap() { return gameMap; }
};


#endif //FAMILY_BUSINESS_GAME_H
