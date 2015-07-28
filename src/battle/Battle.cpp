//
// Created by TriD on 22.06.2015.
//

#include <algorithm>

#include "Battle.h"
#include "../Application.h"
#include "../game/Party.h"
#include "BattleCreatureAI.h"
#include "../MessageManager.h"

void Battle::updateTurns() {
    auto iter = std::remove_if(turns.begin(), turns.end(), [](BattleCreaturePtr creature){ return creature->isDead(); });
    turns.erase(iter, turns.end());
    std::sort(turns.begin(), turns.end(), [](BattleCreaturePtr creature1, BattleCreaturePtr creature2){ return creature1->getSpeed() > creature2->getSpeed(); });
    current = turns.begin();

    for (auto creature: turns) {
        creature->resetSteps();
    }
}

void Battle::nextCreature() {
    if (isFinished()) {
        Application::getInstance().popState();
        return;
    }

    current++;
    if (current == turns.end()) {
        updateTurns();
    }

    if ((*current)->getType() == Creature::Type::Character) {
        battleMap.calculateMoveable(*current);
    }

    if ((*current)->isDead()) {
        nextCreature();
    }

    if ((*current)->getType() == Creature::Type::Monster) {
        static_cast<BattleCreatureAI*>(current->get())->updateTarget();
    }
}

void Battle::makeTurn() {
    if ((*current)->getType() == Creature::Type::Monster) {
        BattleCreatureAI* monster = static_cast<BattleCreatureAI*>((*current).get());
        BattleCreaturePtr target = monster->getTarget();
        Point distance = target->getPosition() - (*current)->getPosition();
        if (abs(distance.x + distance.y) == 1) {
            target->takeDamage((*current)->getAttack());
            nextCreature();
            return;
        }
        else {
            if (monster->getSteps() == 0) {
                nextCreature();
                return;
            }
            if (abs(distance.x) >= 1) {
                const Point& monsterPosition = monster->getPosition();
                battleMap.getTile(monsterPosition.x, monsterPosition.y).setCreature(nullptr);
                monster->setPosition(Point{monsterPosition.x + (distance.x > 0 ? 1 : -1), monsterPosition.y});
                battleMap.getTile(monster->getPosition().x, monster->getPosition().y).setCreature(*current);
            }
            else if (abs(distance.y) >= 1) {
                const Point& monsterPosition = monster->getPosition();
                battleMap.getTile(monsterPosition.x, monsterPosition.y).setCreature(nullptr);
                monster->setPosition(Point{monsterPosition.x, monsterPosition.y + (distance.y > 0 ? 1 : -1)});
                battleMap.getTile(monster->getPosition().x, monster->getPosition().y).setCreature(*current);
            }
            monster->setSteps(monster->getSteps() - 1);
        }
    }
}

Battle::Battle(PartyPtr first, PartyPtr second) : battleMap() {
    std::vector<CreaturePtr> &leftCreatures = first->getCreatures();
    for (int i = 0; i < leftCreatures.size(); i++) {
        BattleCreaturePtr battleCreaturePtr;
        if (leftCreatures[i]->type() == Creature::Type::Character) {
            battleCreaturePtr = std::make_shared<BattleCreature>(leftCreatures[i]);
        }
        else {
            battleCreaturePtr = std::make_shared<BattleCreatureAI>(leftCreatures[i], right);
        }
        battleCreaturePtr->setPosition({0, i});
        battleMap.getTile(0, i).setCreature(battleCreaturePtr);
        left.push_back(battleCreaturePtr);
        turns.push_back(battleCreaturePtr);
    }

    std::vector<CreaturePtr> &rightCreatures = second->getCreatures();
    for (int i = 0; i < rightCreatures.size(); i++) {
        BattleCreaturePtr battleCreaturePtr;
        if (rightCreatures[i]->type() == Creature::Type::Character) {
            battleCreaturePtr = std::make_shared<BattleCreature>(rightCreatures[i]);
        }
        else {
            battleCreaturePtr = std::make_shared<BattleCreatureAI>(rightCreatures[i], left);
        }
        battleCreaturePtr->setPosition({14, 14 - i});
        battleMap.getTile(14, 14 - i).setCreature(battleCreaturePtr);
        right.push_back(battleCreaturePtr);
        turns.push_back(battleCreaturePtr);
    }

    current = std::prev(turns.end());
    nextCreature();
}

void Battle::makeAttack(Point targetPosition) {
    BattleCreaturePtr targetCreature = battleMap.getTile(targetPosition.x, targetPosition.y).getCreature();
    if (targetCreature) {
        BattleCreaturePtr currentCreature = (*current);
        targetCreature->takeDamage(currentCreature->getAttack());
        nextCreature();
    }
}

bool Battle::isFinished() {
    bool playerAlive = false;
    for (auto character: left) {
        playerAlive = playerAlive || !character->isDead();
    }

    if (!playerAlive) {
        return true;
    }

    bool monstersAlive = false;
    for (auto character: right) {
        monstersAlive = monstersAlive || !character->isDead();
    }

    if (!monstersAlive) {
        int exp = right.size() * 100;
        int aliveCharacters = std::count_if(left.begin(), left.end(), [](BattleCreaturePtr battleCreaturePtr){ return !battleCreaturePtr->isDead(); });
        int share = exp / aliveCharacters;

        for (auto character: left) {
            if (!character->isDead()) {
                character->getCreature()->addExperience(share);
            }
        }

        MessageManager::getInstance().sendMessage("player_win", MessageParameters());
    }

    return !monstersAlive;
}
