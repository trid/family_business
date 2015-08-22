//
// Created by TriD on 14.08.2015.
//

#ifndef FAMILY_BUSINESS_PARTYMANAGER_H
#define FAMILY_BUSINESS_PARTYMANAGER_H

#include <fstream>
#include <memory>
#include <vector>

#include "Party.h"

using PartyPtr = std::unique_ptr<Party>;
using Parties = std::vector<PartyPtr>;

class PartyManager {
private:
    Parties parties;
public:
    static PartyManager& getInstance() {
        static PartyManager partyManager;
        return partyManager;
    }
    int createParty(Side side);
    Party& getParty(int id) { return *parties[id]; }
    void clear() { parties.clear(); }

    void save(std::ofstream &out);
};


#endif //FAMILY_BUSINESS_PARTYMANAGER_H
