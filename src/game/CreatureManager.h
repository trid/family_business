//
// Created by TriD on 02.08.2015.
//

#ifndef FAMILY_BUSINESS_CREATUREMANAGER_H
#define FAMILY_BUSINESS_CREATUREMANAGER_H

#include <memory>
#include <vector>

#include "Creature.h"

using CreaturePtr = std::unique_ptr<Creature>;
using Creatures = std::vector<CreaturePtr>;

class CreatureManager {
private:
    CreatureManager() {}

    Creatures creatures;
public:
    static CreatureManager& getInstance() {
        static CreatureManager creatureManager;
        return creatureManager;
    }

    // Using unique_ptr, be careful, original creaturePtr will be nullptr
    int registerCreature(CreaturePtr& creaturePtr);
    int createMonster();
    Creature& getCreatureById(int id) { return *creatures[id]; }
};

// Helper function to get creature by id. Shortcut for CreatureManager::getInstance().getCreatureById(id);
inline Creature& getCreatureById(int id) {
    return CreatureManager::getInstance().getCreatureById(id);
}

#endif //FAMILY_BUSINESS_CREATUREMANAGER_H
