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
}

void MainView::update(int timeDelta) {
    View::update(timeDelta);

    dx += (dxSpeed * timeDelta) / 100;
    dy += (dySpeed * timeDelta) / 100;
    mapView.setDeltas(dx, dy);
}

void MainView::onKeyUp(int key) {
    View::onKeyUp(key);

    if (key == SDLK_LEFT || key == SDLK_RIGHT) dxSpeed = 0;
    if (key == SDLK_UP || key == SDLK_DOWN) dySpeed = 0;
    if (key == SDLK_SPACE) {
        GameMap& gameMap = Game::getInstance().getMap();
        dx = -gameMap.getHousePosX() * 32 - 16 + Screen::getInstance().getWidth() / 2;
        dy = -gameMap.getHousePosY() * 32 - 16 + Screen::getInstance().getHeight() / 2;
        mapView.setDeltas(dx, dy);
    }
}

void MainView::onKeyDown(int key) {
    View::onKeyDown(key);

    switch(key) {
        case SDLK_LEFT:
            dxSpeed = 10;
            break;
        case SDLK_RIGHT:
            dxSpeed = -10;
            break;
        case SDLK_UP:
            dySpeed = 10;
            break;
        case SDLK_DOWN:
            dySpeed = -10;
            break;
        default:break;
    }
}
