//
// Created by TriD on 13.07.2015.
//

#ifndef FAMILY_BUSINESS_FONTSCACHE_H
#define FAMILY_BUSINESS_FONTSCACHE_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <SDL2/SDL_ttf.h>

using FontsMap = std::unordered_map<std::string, TTF_Font*>;

class FontsCache {
private:
    FontsCache() {}

    FontsMap fontsMap;
public:
    static FontsCache& getInstance() {
        static FontsCache fontsCache;
        return fontsCache;
    }

    TTF_Font* getFont(std::string name, int size) {
        std::stringstream ss;
        ss << name << "," << size;

        const std::string &fontName = ss.str();
        if (fontsMap.find(fontName) == fontsMap.end()) {
            fontsMap[fontName] = TTF_OpenFont(name.c_str(), size);
        }
        return fontsMap[fontName];
    }
};


#endif //FAMILY_BUSINESS_FONTSCACHE_H
