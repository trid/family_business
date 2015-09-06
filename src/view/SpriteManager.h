//
// Created by TriD on 19.07.2015.
//

#ifndef FAMILY_BUSINESS_SPRITEMANAGER_H
#define FAMILY_BUSINESS_SPRITEMANAGER_H

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Screen.h"

namespace MEng {
    namespace View {

        using SpriteCache = std::unordered_map<std::string, SDL_Texture *>;

        class SpriteManager {
        private:
            SpriteCache spriteCache;
        public:
            static SpriteManager &getInstance() {
                static SpriteManager instance;
                return instance;
            }

            SDL_Texture *getTexture(std::string name) {
                if (spriteCache.find(name) == spriteCache.end()) {
                    spriteCache[name] = IMG_LoadTexture(Screen::getInstance().getRenderer(), name.c_str());
                }
                return spriteCache[name];
            }
        };

    }
}

#endif //FAMILY_BUSINESS_SPRITEMANAGER_H
