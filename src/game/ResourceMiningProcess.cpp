//
// Created by TriD on 23.09.2015.
//

#include "ResourceMiningProcess.h"
#include "Party.h"
#include "PartyManager.h"
#include "Character.h"
#include "CreatureManager.h"

void Main::ResourceMiningProcess::update(int delta) {
    time += delta;
    if (time >= 1000) {
        time -= 1000;
        Character& character = static_cast<Character&>(CreatureManager::getInstance().getCreatureById(characterId));
        character.addWood();
    }
}

bool Main::ResourceMiningProcess::isFinished() {
    Party& party = PartyManager::getInstance().getParty(partyId);
    return party.isMoving() || stopped;
}

void Main::ResourceMiningProcess::save(std::ofstream &out) {

}

void Main::ResourceMiningProcess::load(std::ifstream &in) {

}

void Main::ResourceMiningProcess::stop() {
    stopped = true;
}
