//
// Created by TriD on 21.06.2015.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "BattleView.h"
#include "../game/Creature.h"

void BattleView::draw() {
    View::draw();
    SDL_Renderer *renderer = Screen::getInstance().getRenderer();
    const BattleMap& gameMap = battle.getBattleMap();

    for (int x = 0; x < gameMap.width; x++) {
        for (int y = 0; y < gameMap.width; y++) {
            SDL_Rect dst{x * 32 + dx, y * 32 + dy, 32, 32};
            SDL_RenderCopy(renderer, grass, nullptr, &dst);
            BattleCreaturePtr creature = gameMap.getTile(x, y).getCreature();
            if (creature) {
                if (creature->getType() == Creature::Type::Character) {
                    SDL_Rect playerDst{x * 32 + dx, y * 32 - 28 + dy, 32, 60};
                    SDL_RenderCopy(renderer, character, nullptr, &playerDst);
                }
                else {
                    SDL_RenderCopy(renderer, monster, nullptr, &dst);
                }
            }
        }
    }
}

BattleView::BattleView(Battle &battle) : battle(battle) {
    Screen &screen = Screen::getInstance();
    SDL_Renderer *renderer = screen.getRenderer();
    grass = IMG_LoadTexture(renderer, "res/images/grass.png");
    character = IMG_LoadTexture(renderer, "res/images/human.png");
    monster = IMG_LoadTexture(renderer, "res/images/monster.png");
    dx = (screen.getWidth() - 15 * 32) / 2;
    dy = (screen.getHeight() - 15 * 32) / 2;
}
