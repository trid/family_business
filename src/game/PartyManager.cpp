//
// Created by TriD on 14.08.2015.
//

#include "PartyManager.h"

int PartyManager::createParty(Side side) {
    parties.emplace_back(PartyPtr(new Party(side, parties.size())));
    return parties.size() - 1;
}

void PartyManager::save(std::ofstream &out) {
    int count = parties.size();
    out.write((char*)count, sizeof(count));

    for (auto& item: parties) {
        item->save(out);
    }
}
