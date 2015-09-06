//
// Created by TriD on 24.05.2015.
//

#include "BattleState.h"
#include "../MessageParameters.h"
#include "../MessageManager.h"

using MEng::View::Screen;

void BattleState::onActivate() {
    MEng::State::onActivate();
}

void BattleState::run() {
    MEng::State::run();
    battle.makeTurn();

    unsigned int ticks = SDL_GetTicks();
    unsigned int delta = ticks - lastTime;
    lastTime = ticks;
    getView()->update(delta);
}

void BattleState::onClick(const Point &point, int button) {
    MEng::State::onClick(point, button);

    if (battle.isBlockInput()) {
        return;
    }

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
            Point diff = Point{posX, posY} - current->getPosition();
            int dist = std::abs(diff.x) + std::abs(diff.y);
            if (dist > current->getSteps()) {
                return;
            }
            current->setSteps(current->getSteps() - dist);
            battleMap.getTile(current->getPosition().x, current->getPosition().y).setCreature(nullptr);
            tile.setCreature(current);
            current->setPosition({posX, posY});
            battle.getBattleMap().calculateMoveable(current);
            MEng::MessageParameters messageParameters;
            messageParameters.setParameter("dx", diff.x);
            messageParameters.setParameter("dy", diff.y);
            MEng::MessageManager::getInstance().sendMessage("creature_moving", messageParameters);
        }
    }
}
