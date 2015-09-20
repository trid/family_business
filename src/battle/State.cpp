//
// Created by TriD on 24.05.2015.
//

#include "State.h"
#include "../MessageParameters.h"
#include "../MessageManager.h"

using MEng::View::Screen;
using namespace BattleState;
using namespace BattleState::View;

void State::onActivate() {
    MEng::State::onActivate();
}

void State::run() {
    MEng::State::run();
    battle.makeTurn();

    unsigned int ticks = SDL_GetTicks();
    unsigned int delta = ticks - lastTime;
    lastTime = ticks;
    getView()->update(delta);
}

void State::onClick(const Point &point, int button) {
    MEng::State::onClick(point, button);

    if (battle.isBlockInput()) {
        return;
    }

    BattleState::BattleCreaturePtr current = *battle.getCurrent();
    if (current->getSide() != Main::Side::Player) {
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

    BattleState::BattleMap &battleMap = battle.getBattleMap();
    BattleTile &tile = battleMap.getTile(posX, posY);
    BattleState::BattleCreaturePtr creature = tile.getCreature();
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
