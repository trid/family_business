//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"
#include "../game/House.h"
#include "../game/Game.h"

void MainView::draw() {
    mapView.draw(Screen::getInstance().getRenderer());
    View::draw();
}

MainView::MainView() {
    UILayout& layout = getLayout();
    familyDialogWidget = WidgetPtr{new ChoseFamilyDialog((800 - 200) / 2, (600 - 60) / 2, 200, 0,
                                                       [this](FamilyPtr familyPtr) { showFamilyDialog(familyPtr); })};
    familyDialogWidget->show();
    layout.addWidget(familyDialogWidget);
    choseCharacterDialog = ChoseCharacterDialogPtr{new ChoseCharacterDialog((800 - 200) / 2, (600 - 60) / 2, 200, 60,
                                     [this](CharacterPtr characterPtr) { choseCharacter(characterPtr); })};
    choseCharacterDialog->hide();
    layout.addWidget(choseCharacterDialog);
}

void MainView::showFamilyDialog(FamilyPtr familyPtr) {
    familyDialogWidget->hide();
    choseCharacterDialog->setUp(familyPtr);
    choseCharacterDialog->show();
}

void MainView::choseCharacter(CharacterPtr characterPtr) {
    choseCharacterDialog->hide();
    Game::getInstance().setPlayerCharacter(characterPtr);
    GameMap& gameMap = Game::getInstance().getMap();
    int posX = gameMap.getHousePosX();
    int posY = gameMap.getHousePosY();
    gameMap.getTile(posX, posY)->setCreature(characterPtr);
    characterPtr->setX(posX);
    characterPtr->setY(posY);
    centerOnCharacter();
}

void MainView::update(int timeDelta) {
    View::update(timeDelta);

    centerOnCharacter();
    mapView.setDeltas(dx, dy);
}

void MainView::onKeyUp(int key) {
    View::onKeyUp(key);
}

void MainView::onKeyDown(int key) {
    View::onKeyDown(key);
}

void MainView::centerOnCharacter() {
    CharacterPtr character = Game::getInstance().getPlayerCharacter();
    if (character) {
        GameMap& gameMap = Game::getInstance().getMap();
        dx = -character->getX() * 32 - 16 + Screen::getInstance().getWidth() / 2;
        dy = -character->getY() * 32 - 16 + Screen::getInstance().getHeight() / 2;
        mapView.setDeltas(dx, dy);
    }
}
