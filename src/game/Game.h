//
// Created by TriD on 14.06.2015.
//

#ifndef FAMILY_BUSINESS_GAME_H
#define FAMILY_BUSINESS_GAME_H


#include "CharacterManager.h"
#include "GameMap.h"
#include "Party.h"

class Game {
private:
    CharacterPtr playerCharacter;
    HousePtr housePtr;
    GameMap gameMap;
    PartyPtr playerParty{new Party(Side::Player)};

    Game();

public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    GameMap &getMap() { return gameMap; }

    CharacterPtr getPlayerCharacter() const { return playerCharacter; }
    PartyPtr getPlayerParty() { return playerParty; }

    void setPlayerCharacter(CharacterPtr playerCharacter) {
        Game::playerCharacter = playerCharacter;
        playerParty->addCreature(playerCharacter);
    }
};


#endif //FAMILY_BUSINESS_GAME_H
