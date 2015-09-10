//
// Created by TriD on 04.09.2015.
//

#include "CharacterAI.h"
#include "Character.h"
#include "CreatureManager.h"
#include "Game.h"

using namespace Main;

void CharacterAI::update(int delta) {
    if (characterId == Game::getInstance().getPlayerCharacter().getId()) {
        return;
    }
    CreatureManager &creatureManager = CreatureManager::getInstance();
    Character& character = static_cast<Character&>(creatureManager.getCreatureById(characterId));
    if (!character.isMarried() && character.getAge() >= 16 * 12 * 30) {
        auto characters = creatureManager.getCharactersByGender(character.getGender() == Gender::Male ? Gender::Female : Gender::Male);
        if (!characters.empty()) {
            for (int id: characters) {
                Character& partner = static_cast<Character&>(creatureManager.getCreatureById(id));
                if (!partner.isMarried()) {
                    Game::getInstance().marry(character.getId(), partner.getId());
                }
            }
        }
    }
}
