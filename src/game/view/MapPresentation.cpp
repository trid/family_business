//
// Created by TriD on 15.06.2015.
//

#include <SDL2/SDL_image.h>

#include "MapPresentation.h"
#include "../../view/Screen.h"
#include "../GameMap.h"
#include "../Game.h"

MapPresentation::MapPresentation() {
    SDL_Renderer* renderer = Screen::getInstance().getRenderer();
    grass = IMG_LoadTexture(renderer, "res/images/grass.png");
    house = IMG_LoadTexture(renderer, "res/images/house.png");
    character = IMG_LoadTexture(renderer, "res/images/human.png");
    monster = IMG_LoadTexture(renderer, "res/images/monster.png");
}

void MapPresentation::draw(SDL_Renderer *renderer) {
    GameMap& gameMap = Game::getInstance().getMap();

    for (int x = 0; x < gameMap.getWidth(); x++) {
        for (int y = 0; y < gameMap.getHeight(); y++) {
            SDL_Rect dst{x * 32 + dx, y * 32 + dy, 32, 32};
            SDL_RenderCopy(renderer, grass, nullptr, &dst);
            if (gameMap.getTile(x, y).getHouse()){
                SDL_RenderCopy(renderer, house, nullptr, &dst);
            }
            PartyPtr party = gameMap.getTile(x, y).getParty();
            if (party) {
                if (party->getSide() == Side::Player) {
                    SDL_Rect playerDst{x * 32 + dx, y * 32 + dy - 28, 32, 60};
                    SDL_RenderCopy(renderer, character, nullptr, &playerDst);
                }
                else {
                    SDL_RenderCopy(renderer, monster, nullptr, &dst);
                }
            }
        }
    }
}

void MapPresentation::update(int timeDelta) {

}
