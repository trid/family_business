//
// Created by TriD on 02.08.2015.
//

#include "CreatureManager.h"
#include "Monster.h"
#include "Character.h"
#include "Side.h"

using namespace Main;

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

void CreatureManager::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        Creature::Type type;
        in.read(reinterpret_cast<char*>(&type), sizeof(type));
        if (type == Creature::Type::Character) {
            creatures.emplace_back(new Main::Character(in));
        }
        else {
            creatures.emplace_back(new Monster(in));
        }
    }
}

void CreatureManager::updateAge() {
    for (auto& item: creatures) {
        if (item->type() == Creature::Type::Character) {
            Main::Character* character = static_cast<Main::Character*>(item.get());
            character->addDay();
        }
    }
}

std::vector<int> CreatureManager::getCharactersByGender(Main::Gender gender) {
    std::vector<int> characters;

    for (auto& creature: creatures) {
        if (creature->type() == Creature::Type::Character && static_cast<Main::Character*>(creature.get())->getGender() == gender) {
            characters.push_back(creature->getId());
        }
    }

    return characters;
}
