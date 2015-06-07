//
// Created by TriD on 24.05.2015.
//

#include "MainState.h"
#include "CharacterManager.h"

MainState::MainState(): view{new MainView()} {
    CharacterManager& characterManager = CharacterManager::getInstance();

    for (int i = 0; i < 3; i++) {
        CharacterPtr father = characterManager.addCharacter(Gender::Male);
        CharacterPtr mother = characterManager.addCharacter(father->getLastName(), Gender::Female);
        Children children;
        for (int j = 0; j < 3; j++) {
            children.push_back(characterManager.addCharacter(father->getLastName()));
        }
        FamilyPtr family{new Family(father, mother, children)};
        families.push_back(family);
    }
}

void MainState::onClick(const Point &point, int button) {
    State::onClick(point, button);
    view->onClick(point, button);
}

void MainState::onActivate() {
    State::onActivate();
    Screen::getInstance().setView(view);
}
