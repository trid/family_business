//
// Created by TriD on 15.06.2015.
//

#include <SDL2/SDL_image.h>

#include "MapPresentation.h"
#include "../../view/Screen.h"
#include "../GameMap.h"
#include "../Game.h"
#include "../../MessageManager.h"
#include "../../view/SpriteManager.h"
#include "../BuildingManager.h"

using namespace MEng;
using namespace MEng::View;
using namespace Main;
using namespace Main::View;

MapPresentation::MapPresentation() {
    SDL_Renderer* renderer = Screen::getInstance().getRenderer();
    grass = IMG_LoadTexture(renderer, "res/images/grass.png");
    house = IMG_LoadTexture(renderer, "res/images/house.png");
    character = IMG_LoadTexture(renderer, "res/images/human.png");
    monster = IMG_LoadTexture(renderer, "res/images/monster.png");
    tree = SpriteManager::getInstance().getTexture("res/images/tree.png");
    road = SpriteManager::getInstance().getTexture("res/images/road.png");

    MessageListenerPtr moveListener = std::make_shared<CharacterMoveListener>(*this);
    MessageManager::getInstance().addListener("character_moved", moveListener);
}

void MapPresentation::draw(SDL_Renderer *renderer) {
    GameMap& gameMap = Game::getInstance().getMap();
    Screen& screen = Screen::getInstance();
    BuildingManager &manager = BuildingManager::getInstance();

    for (int x = -dx / 32; x < (-dx + screen.getWidth() - 150) / 32 + 1 && x < gameMap.getWidth(); x++) {
        for (int y = -dy / 32; y < ((-dy + screen.getHeight()) / 32 + 1) && y < gameMap.getHeight(); y++) {
            SDL_Rect dst{x * 32 + dx, y * 32 + dy, 32, 32};
            SDL_RenderCopy(renderer, grass, nullptr, &dst);
            Tile &tile = gameMap.getTile(x, y);
            if (tile.getLandscapeType() == LandscapeType::Forest) {
                SDL_RenderCopy(renderer, tree, nullptr, &dst);
            }
            int buildingId = tile.getBuilding();
            if (buildingId != -1){
                Main::Building& building = manager.getBuilding(buildingId);
                if (building.getType() != Main::BuildingType::Road) {
                    SDL_RenderCopy(renderer, house, nullptr, &dst);
                }
                else {
                    SDL_RenderCopy(renderer, road, nullptr, &dst);
                }
            }
        }
    }
}

void MapPresentation::update(int timeDelta) {

}

void MapPresentation::CharacterMoveListener::onMessage(const MessageParameters &messageParameters) {
    int partyId = messageParameters.getParameter("partyId").getInt();

    if (partyId == Game::getInstance().getPlayerParty().getId()) {
        int x = messageParameters.getParameter("x").getInt();
        int y = messageParameters.getParameter("y").getInt();

        int dx = -x * 32 - 16 + (Screen::getInstance().getWidth() - 150) / 2;
        int dy = -y * 32 - 16 + Screen::getInstance().getHeight() / 2;

        mapPresentation.setDeltas(dx, dy);
    }
}

void MapPresentation::setDeltas(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
    if (this->dx >= 0) {
        this->dx = 0;
    }
    if (this->dy >= 0) {
        this->dy = 0;
    }
    int mapWidth = Game::getInstance().getMap().getWidth();
    int mapHeight = Game::getInstance().getMap().getHeight();
    int maxDx = -mapWidth * 32 + Screen::getInstance().getWidth() - 150;
    int maxDy = -mapHeight * 32 + Screen::getInstance().getHeight();
    if (this->dx <= maxDx) {
        this->dx = maxDx;
    }
    if (this->dy <= maxDy) {
        this->dy = maxDy;
    }
}
