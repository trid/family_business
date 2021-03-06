//
// Created by TriD on 02.08.2015.
//

#ifndef FAMILY_BUSINESS_CREATUREMANAGER_H
#define FAMILY_BUSINESS_CREATUREMANAGER_H

#include <fstream>
#include <memory>
#include <vector>

#include "Creature.h"
#include "Character.h"

namespace Main {

    using CreaturePtr = std::unique_ptr<Main::Creature>;
    using Creatures = std::vector<CreaturePtr>;

    class CreatureManager {
    private:
        CreatureManager() { }

        Creatures creatures;
    public:
        static CreatureManager &getInstance() {
            static CreatureManager creatureManager;
            return creatureManager;
        }

        // Using unique_ptr, be careful, original creaturePtr will be nullptr
        int registerCreature(CreaturePtr &creaturePtr);

        int createMonster();

        Main::Creature &getCreatureById(int id) { return *creatures[id]; }

        std::vector<int> getCharactersByGender(Main::Gender gender);

        void updateAge();

        void clear() { creatures.clear(); }

        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

// Helper function to get creature by id. Shortcut for CreatureManager::getInstance().getCreatureById(id);
    inline Main::Creature &getCreatureById(int id) {
        return CreatureManager::getInstance().getCreatureById(id);
    }

}

#endif //FAMILY_BUSINESS_CREATUREMANAGER_H
