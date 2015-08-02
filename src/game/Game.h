//
// Created by TriD on 14.06.2015.
//

#ifndef FAMILY_BUSINESS_GAME_H
#define FAMILY_BUSINESS_GAME_H


#include "CharacterManager.h"
#include "GameMap.h"
#include "Party.h"
#include "CreatureManager.h"

class Game {
private:
    int playerCharacter;
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

    Character& getPlayerCharacter() const { return static_cast<Character&>(getCreatureById(playerCharacter)); }
    PartyPtr getPlayerParty() { return playerParty; }

    void setPlayerCharacter(int playerCharacter) {
        Game::playerCharacter = playerCharacter;
        playerParty->addCreature(playerCharacter);
    }
};


#endif //FAMILY_BUSINESS_GAME_H
