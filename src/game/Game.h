//
// Created by TriD on 14.06.2015.
//

#ifndef FAMILY_BUSINESS_GAME_H
#define FAMILY_BUSINESS_GAME_H


#include "CharacterManager.h"
#include "GameMap.h"
#include "Party.h"
#include "CreatureManager.h"
#include "PartyManager.h"

class Game {
private:
    int playerCharacter;
    GameMap gameMap;
    int playerParty;

    Game();

public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    GameMap &getMap() { return gameMap; }

    Character& getPlayerCharacter() const { return static_cast<Character&>(getCreatureById(playerCharacter)); }
    Party& getPlayerParty() { return PartyManager::getInstance().getParty(playerParty); }

    void setPlayerCharacter(int playerCharacter) {
        Game::playerCharacter = playerCharacter;
        getPlayerParty().addCreature(playerCharacter);
    }

    void newGame();
    void saveGame();
};


#endif //FAMILY_BUSINESS_GAME_H
