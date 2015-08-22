//
// Created by TriD on 02.08.2015.
//

#include "CreatureManager.h"
#include "Monster.h"

int CreatureManager::registerCreature(CreaturePtr &creaturePtr) {
    creaturePtr->id = creatures.size();
    creatures.push_back(std::move(creaturePtr));
    return creatures.size() - 1;
}

int CreatureManager::createMonster() {
    Monster *monster = new Monster();
    monster->id = creatures.size();
    creatures.emplace_back(monster);
    return creatures.size() - 1;
}

void CreatureManager::save(std::ofstream &out) {
    int count = creatures.size();
    out.write((char*)&count, sizeof(count));

    for (auto& item: creatures) {
        item->save(out);
    }
}
