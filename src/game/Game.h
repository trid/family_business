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
#include "Movement.h"

namespace Main {

    class Game {
    private:
        int playerCharacter{-1};
        GameMap gameMap;
        int playerParty{-1};
        long int days{0l};
        //TODO: change to process in future
        int dateDelta{0};

        std::vector<MovementPtr> movement;

        Game();

    public:
        static Game &getInstance() {
            static Game instance;
            return instance;
        }

        GameMap &getMap() { return gameMap; }

        Character &getPlayerCharacter() const { return static_cast<Character &>(getCreatureById(playerCharacter)); }

        Party &getPlayerParty() { return PartyManager::getInstance().getParty(playerParty); }

        void setPlayerCharacter(int playerCharacter) {
            Game::playerCharacter = playerCharacter;
            getPlayerParty().addCreature(playerCharacter);
        }

        void addDay();

        int getDate() { return days; }

        void moveParty(int partyId, Point newPosition);

        void marry(int character1, int character2);

        void update(int delta);

        void newGame();

        void saveGame();

        void loadGame();
    };

}

#endif //FAMILY_BUSINESS_GAME_H
