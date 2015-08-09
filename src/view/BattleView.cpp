//
// Created by TriD on 21.06.2015.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "BattleView.h"
#include "../game/Creature.h"
#include "SpriteManager.h"
#include "../MessageManager.h"
#include "MovementAnimation.h"

void BattleView::draw(SDL_Renderer *renderer) {
    const BattleMap& gameMap = battle.getBattleMap();

    for (int x = 0; x < gameMap.width; x++) {
        for (int y = 0; y < gameMap.width; y++) {
            SDL_Rect dst{x * 32 + dx, y * 32 + dy, 32, 32};
            SDL_RenderCopy(renderer, grass, nullptr, &dst);
            const BattleTile &tile = gameMap.getTile(x, y);
            if (tile.getCanMove()) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
                SDL_RenderFillRect(renderer, &dst);
            }
            /*BattleCreaturePtr creature = tile.getCreature();
            if (creature) {
                if (creature->getType() == Creature::Type::Character) {
                    SDL_Rect playerDst{x * 32 + dx, y * 32 - 28 + dy, 32, 60};
                    SDL_RenderCopy(renderer, character, nullptr, &playerDst);
                }
                else {
                    SDL_RenderCopy(renderer, monster, nullptr, &dst);
                }
            }*/
        }
    }
    BattleCreaturePtr current = *battle.getCurrent();
    Point currentPosition = current->getPosition();
    SDL_Rect pos;
    if (current->getType() == Creature::Type::Character) {
        pos = {currentPosition.x * 32 + 12 + dx, currentPosition.y * 32 - 38 + dy, 8, 8};
    }
    else {
        pos = {currentPosition.x * 32 + 12 + dx, currentPosition.y * 32 - 10 + dy, 8, 8};
    }
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &pos);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    View::draw(renderer);
}

BattleView::BattleView(Battle &battle) : battle(battle) {
    Screen &screen = Screen::getInstance();
    SDL_Renderer *renderer = screen.getRenderer();
    grass = IMG_LoadTexture(renderer, "res/images/grass.png");
    character = IMG_LoadTexture(renderer, "res/images/human.png");
    monster = IMG_LoadTexture(renderer, "res/images/monster.png");
    dx = (screen.getWidth() - 15 * 32) / 2;
    dy = (screen.getHeight() - 15 * 32) / 2;

    auto& left = battle.getLeft();
    auto& right = battle.getRight();
    battleCreaturesView.resize(left.size() + right.size());

    //TODO: refactor this. There is a better way.
    for (auto& item: left) {
        Creature::Type type = item->getType();
        int id = item->getId();
        SDL_Texture* sprite;
        Point position{};
        if (type == Creature::Type::Character) {
            sprite = SpriteManager::getInstance().getTexture("res/images/human.png");
            position.x = item->getPosition().x * 32 + dx;
            position.y = item->getPosition().y * 32 + dy - 28;
        }
        else {
            sprite = SpriteManager::getInstance().getTexture("res/images/monster.png");
            position.x = item->getPosition().x * 32 + dx;
            position.y = item->getPosition().y * 32 + dy;
        }
        battleCreaturesView[item->getId()] = std::make_shared<Image>(sprite, position);
    }

    for (auto& item: right) {
        Creature::Type type = item->getType();
        int id = item->getId();
        SDL_Texture* sprite;
        Point position{};
        if (type == Creature::Type::Character) {
            sprite = SpriteManager::getInstance().getTexture("res/images/human.png");
            position.x = item->getPosition().x * 32 + dx;
            position.y = item->getPosition().y * 32 + dy - 28;
        }
        else {
            sprite = SpriteManager::getInstance().getTexture("res/images/monster.png");
            position.x = item->getPosition().x * 32 + dx;
            position.y = item->getPosition().y * 32 + dy;
        }
        battleCreaturesView[item->getId()] = std::make_shared<Image>(sprite, position);
    }

    for (auto item: battleCreaturesView) {
        addDrawable(item);
    }

    MessageManager &messageManager = MessageManager::getInstance();
    messageManager.addListener("creature_moving", std::make_shared<CreatureMovingListener>(*this));
    messageManager.addListener("movement_animation_finished", std::make_shared<AnimationFinishedListener>(*this));
}

void BattleView::CreatureMovingListener::onMessage(const MessageParameters &messageParameters) {
    int dx = messageParameters.getParameter("dx").getInt();
    int dy = messageParameters.getParameter("dy").getInt();
    battleView.movements.push(std::make_pair((*battleView.battle.getCurrent())->getId(), Point{dx, dy}));
    battleView.startMovementAnimation();
}

void BattleView::startMovementAnimation() {
    if (!movements.empty() && !showingAnimation) {
        battle.setBlockInput(true);
        auto target = movements.front();
        ImagePtr imagePtr = battleCreaturesView[target.first];
        target.second.x *= 32;
        target.second.y *= 32;
        movements.pop();
        AnimationPtr animationPtr{new MovementAnimation(imagePtr, imagePtr->getPosition() + target.second, 500)};
        addAnimation(animationPtr);
        showingAnimation = true;
    }
}

void BattleView::AnimationFinishedListener::onMessage(const MessageParameters &messageParameters) {
    battleView.showingAnimation = false;
    battleView.battle.setBlockInput(false);
    battleView.startMovementAnimation();
}
