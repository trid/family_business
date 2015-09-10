//
// Created by TriD on 01.09.2015.
//

#include "MonsterAI.h"
#include "Party.h"
#include "PartyManager.h"
#include "Game.h"

using namespace Main;

void MonsterAI::update(int delta) {
    time += delta;
    if (time >= 1000) {
        time -= 1000;

        int direction = distributor(generator);
        int dx{0};
        int dy{0};
        switch (direction) {
            case 0:
                dx = 1;
                break;
            case 1:
                dx = -1;
                break;
            case 2:
                dy = 1;
                break;
            case 3:
                dy = -1;
                break;
            default:
                break;
        }

        Party& party = PartyManager::getInstance().getParty(monsterPartyId);
        Point position = party.getPosition();
        Point directionPoint{position.x + dx, position.y + dy};
        if (directionPoint.x >= 0 && directionPoint.x <= 127 && directionPoint.y >= 0 && directionPoint.y <= 127) {
            Game::getInstance().moveParty(monsterPartyId, directionPoint);
        }
    }
}
