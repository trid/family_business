//
// Created by TriD on 22.06.2015.
//

#include <algorithm>

#include "Battle.h"

void Battle::updateTurns() {
    std::sort(turns.begin(), turns.end(), [](BattleCreaturePtr creature1, BattleCreaturePtr creature2){ return creature1->getSpeed() > creature2->getSpeed(); });
    current = turns.begin();
    for (auto creature: turns) {
        creature->resetSteps();
    }
}

void Battle::nextCreature() {
    if (current == turns.end()) {
        updateTurns();
    }
    else {
        current++;
    }
}

void Battle::makeTurn() {
    if ((*current)->getType() == Creature::Type::Monster) {
        BattleCreaturePtr monster = *current;
        BattleCreaturePtr target = (*current)->getTarget();
        Point distance = target->getPosition() - (*current)->getPosition();
        if (abs(distance.x + distance.y) == 1) {
            target->takeDamage((*current)->getAttack());
            nextCreature();
        }
        else {
            if (monster->getSteps() == 0) {
                nextCreature();
            }
            if (abs(distance.x) >= 1) {
                const Point& monsterPosition = monster->getPosition();
                battleMap.getTile(monsterPosition.x, monsterPosition.y).setCreature(nullptr);
                monster->setPosition(Point{monsterPosition.x + (distance.x > 0 ? 1 : -1), monsterPosition.y});
                battleMap.getTile(monster->getPosition().x, monster->getPosition().y).setCreature(monster);
            }
            else if (abs(distance.y) >= 1) {
                const Point& monsterPosition = monster->getPosition();
                battleMap.getTile(monsterPosition.x, monsterPosition.y).setCreature(nullptr);
                monster->setPosition(Point{monsterPosition.x, monsterPosition.y + (distance.y > 0 ? 1 : -1)});
                battleMap.getTile(monster->getPosition().x, monster->getPosition().y).setCreature(monster);
            }
            monster->setSteps(monster->getSteps() - 1);
        }
    }
}

Battle::Battle(CreaturePtr character, CreaturePtr monster) : battleMap(), character(new BattleCreature(character)),
                                                             monster(new BattleCreature(monster)) {
    this->monster->setTarget(this->character);
    this->character->setPosition({0, 0});
    this->monster->setPosition({14, 14});
    battleMap.getTile(0, 0).setCreature(this->character);
    battleMap.getTile(14, 14).setCreature(this->monster);
    turns.push_back(this->monster);
    turns.push_back(this->character);
    updateTurns();
}
