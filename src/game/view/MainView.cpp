//
// Created by dmitry-khovyakov on 5/25/15.
//

#include <algorithm>

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"
#include "../House.h"
#include "../Game.h"

void MainView::draw(SDL_Renderer *renderer) {
    View::draw(renderer);
}

MainView::MainView() {
    UILayout &layout = getLayout();
    ChoseFamilyDialog *dialog = new ChoseFamilyDialog((800 - 200) / 2, (600 - 60) / 2, 200, 0, layout,
                                                      [this](FamilyPtr familyPtr) { showFamilyDialog(familyPtr); });
    familyDialogWidget = WidgetPtr{dialog};
    dialog->setUp();
    dialog->show();
    layout.addWidget(familyDialogWidget);
    choseCharacterDialog = ChoseCharacterDialogPtr{
            new ChoseCharacterDialog((800 - 200) / 2, (600 - 60) / 2, 200, 60, layout,
                                     [this](int characterId) { choseCharacter(characterId); })};
    layout.addWidget(choseCharacterDialog);

    auto addCharacterToParty = [this](int characterId) {
        this->addCharacterToParty(characterId, {});
    };

    hireCharacterDialog = std::make_shared<HireCharacterDialog>((800 - 200) / 2, (600 - 60) / 2, 200, 60, layout,
                                                                addCharacterToParty);
    layout.addWidget(hireCharacterDialog);

    addDrawable(mapView);
}

void MainView::showFamilyDialog(FamilyPtr familyPtr) {
    familyDialogWidget->hide();
    choseCharacterDialog->setUp(familyPtr);
    choseCharacterDialog->show();
}

void MainView::choseCharacter(int characterId) {
    choseCharacterDialog->hide();
    Game &game = Game::getInstance();
    game.setPlayerCharacter(characterId);
    GameMap &gameMap = game.getMap();
    int posX = gameMap.getHousePosX();
    int posY = gameMap.getHousePosY();
    const PartyPtr party = game.getPlayerParty();
    gameMap.getTile(posX, posY).setParty(party);
    party->setX(posX);
    party->setY(posY);
    centerOnCharacter();
}

void MainView::update(int timeDelta) {
    View::update(timeDelta);
}

void MainView::onKeyUp(int key) {
    View::onKeyUp(key);
}

void MainView::onKeyDown(int key) {
    View::onKeyDown(key);
}

void MainView::centerOnCharacter() {
    PartyPtr party = Game::getInstance().getPlayerParty();
    if (party->getCreatures().size()) {
        GameMap &gameMap = Game::getInstance().getMap();
        dx = -party->getX() * 32 - 16 + Screen::getInstance().getWidth() / 2;
        dy = -party->getY() * 32 - 16 + Screen::getInstance().getHeight() / 2;
        static_cast<MapPresentation *>(mapView.get())->setDeltas(dx, dy);
    }
}

void MainView::showHireDialog(HousePtr housePtr) {
    auto addCharacterToParty = [this, housePtr](int character) {
        this->addCharacterToParty(character, housePtr);
    };
    hireCharacterDialog->setCallback(addCharacterToParty);
    hireCharacterDialog->setUp(housePtr);
    hireCharacterDialog->show();
}

void MainView::addCharacterToParty(int characterPtr, HousePtr housePtr) {
    if (Game::getInstance().getPlayerParty()->addCreature(characterPtr)) {
        std::vector<int>& characters = housePtr->getCharacters();
        auto iter = std::remove(characters.begin(), characters.end(), characterPtr);
        characters.erase(iter, characters.end());
    }
    hireCharacterDialog->hide();
}
