//
// Created by TriD on 24.05.2015.
//

#include "BattleState.h"

void BattleState::onActivate() {
    State::onActivate();
}

void BattleState::run() {
    State::run();
    battle.makeTurn();
}

void BattleState::onClick(const Point &point, int button) {
    State::onClick(point, button);

    BattleCreaturePtr current = *battle.getCurrent();
    if (current->getType() != Creature::Type::Character) {
        return;
    }

    BattleView* battleView = static_cast<BattleView*>(getView().get());
    int dx = (Screen::getInstance().getWidth() - 15 * 32) / 2;
    int dy = (Screen::getInstance().getHeight() - 15 * 32) / 2;

    int posX = (point.x - dx) / 32;
    int posY = (point.y - dy) / 32;

    if (posX < 0 || posY < 0 || posX >= 15 || posY >= 15) {
        return;
    }

    BattleMap &battleMap = battle.getBattleMap();
    BattleTile &tile = battleMap.getTile(posX, posY);
    BattleCreaturePtr creature = tile.getCreature();
    if (creature) {
        battle.makeAttack(Point{posX, posY});
    }
    else {
        if (tile.getCanMove()) {
            Point diff = current->getPosition() - Point{posX, posY};
            int dist = std::abs(diff.x) + std::abs(diff.y);
            if (dist > current->getSteps()) {
                return;
            }
            current->setSteps(current->getSteps() - dist);
            battleMap.getTile(current->getPosition().x, current->getPosition().y).setCreature(nullptr);
            tile.setCreature(current);
            current->setPosition({posX, posY});
            battle.getBattleMap().calculateMoveable(current);
        }
    }
}
