//
// Created by TriD on 02.08.2015.
//

#include "Movement.h"
#include "../MessageManager.h"
#include "PartyManager.h"

void Movement::update(int delta) {
    time += delta;

    if (time >= 500) {
        Party& party = PartyManager::getInstance().getParty(partyId);
        party.setMoving(false);
        MessageParameters parameters;
        parameters.setParameter("x", target.x);
        parameters.setParameter("y", target.y);
        MessageManager::getInstance().sendMessage("movement_finished", parameters);
    }
}

void Movement::save(std::ofstream &out) {
    out.write((char*)&partyId, sizeof(partyId));
    out.write((char*)&target, sizeof(target));
    out.write((char*)&time, sizeof(time));
}

void Movement::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(&partyId), sizeof(partyId));
    in.read(reinterpret_cast<char*>(&target), sizeof(target));
    in.read(reinterpret_cast<char*>(&time), sizeof(time));

    MessageParameters messageParameters;
    messageParameters.setParameter("partyId", partyId);
    messageParameters.setParameter("x", target.x);
    messageParameters.setParameter("y", target.y);
    messageParameters.setParameter("time", time);
    MessageManager::getInstance().enqueuMessage("movement_restart", messageParameters);
}
