//
// Created by TriD on 14.08.2015.
//

#include "PartyManager.h"

using namespace Main;

int PartyManager::createParty(Side side) {
    parties.emplace_back(PartyPtr(new Party(side, parties.size())));
    return parties.size() - 1;
}

void PartyManager::save(std::ofstream &out) {
    int count = parties.size();
    out.write((char*)&count, sizeof(count));

    for (auto& item: parties) {
        item->save(out);
    }
}

void PartyManager::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        parties.emplace_back(new Party(in));
    }
}
