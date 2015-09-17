//
// Created by TriD on 01.09.2015.
//

#include <algorithm>

#include "AIManager.h"
#include "CharacterAI.h"

using namespace Main;

void AIManager::update(int delta) {
    for (auto item: aiItems) {
        item->update(delta);
    }
}

void AIManager::addAi(AbstractAIPtr ai) {
    aiItems.push_back(ai);
}

void AIManager::removeAi(AbstractAIPtr ai) {
    auto iter = std::remove(aiItems.begin(), aiItems.end(), ai);
    aiItems.erase(iter, aiItems.end());
}

void AIManager::removeCharacterAI(int characterId) {
    auto pred = [](AbstractAIPtr ai) {
        auto characterAI = std::dynamic_pointer_cast<CharacterAI>(ai);
        return characterAI != nullptr;
    };
    auto iter = std::remove_if(aiItems.begin(), aiItems.end(), pred);
    aiItems.erase(iter, aiItems.end());
}
