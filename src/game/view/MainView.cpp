//
// Created by dmitry-khovyakov on 5/25/15.
//

#include <algorithm>

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"
#include "../House.h"
#include "../Game.h"
#include "GUI/CharacterPanel.h"
#include "../../view/SpriteManager.h"
#include "../../MessageManager.h"
#include "../../view/MovementAnimation.h"

void MainView::draw(SDL_Renderer *renderer) {
    View::draw(renderer);
}

MainView::MainView() {
    UILayout &layout = getLayout();
    ChoseFamilyDialog *dialog = new ChoseFamilyDialog((800 - 200) / 2, (600 - 60) / 2, 200, 0, layout,
                                                      [this](int familyId) { showFamilyDialog(familyId); });
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
    WidgetPtr sidePanel{new CharacterPanel(650, 0, 150, 600, nullptr)};
    layout.addWidget(sidePanel);

    playerPartyImage = ImagePtr{new Image(SpriteManager::getInstance().getTexture("res/images/human.png"), {800, 600})};

    addDrawable(mapView);
    addDrawable(playerPartyImage);

    MessageManager &messageManager = MessageManager::getInstance();
    messageManager.addListener("character_moved", std::make_shared<CharacterMovedListener>(*this));
    messageManager.addListener("party_moving", std::make_shared<CharacterMovingListener>(*this));
}

void MainView::showFamilyDialog(int familyId) {
    familyDialogWidget->hide();
    choseCharacterDialog->setUp(familyId);
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
    
    Point characterPositionWorld{posX * 32, posY * 32};
    int characterImagePosX = (650 - 32) / 2;
    int characterImagePosY = (600 - 32) / 2 - 28;
    if (characterPositionWorld.x <= (650 - 32) / 2) {
        characterImagePosX = posX * 32;
    }
    if (characterPositionWorld.x >= gameMap.getWidth() * 32 - (650 - 32) / 2) {
        characterImagePosX = (650 - (gameMap.getWidth() - posX) * 32);
    }
    if (characterPositionWorld.y <= (600 - 32) / 2) {
        characterImagePosY = posY * 32 - 28;
    }
    if (characterPositionWorld.y >= gameMap.getHeight() * 32 - (600 - 32) / 2) {
        characterImagePosY = (600 - (gameMap.getWidth() - posX) * 32 - 28);
    }
    playerPartyImage->setPosition({characterImagePosX, characterImagePosY});

    MessageParameters messageParameters;
    messageParameters.setParameter("characterId", characterId);
    MessageManager::getInstance().sendMessage("character_selected", messageParameters);
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
        dx = -party->getX() * 32 - 16 + (Screen::getInstance().getWidth() - 150) / 2;
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

void MainView::CharacterMovedListener::onMessage(const MessageParameters &messageParameters) {
    int x = messageParameters.getParameter("x").getInt();
    int y = messageParameters.getParameter("y").getInt();

    Point characterPositionWorld{x * 32, y * 32};
    int characterImagePosX = (650 - 32) / 2;
    int characterImagePosY = (600 - 32) / 2 - 28;

    GameMap& gameMap = Game::getInstance().getMap();

    if (characterPositionWorld.x <= (650 - 32) / 2) {
        characterImagePosX = x * 32;
    }
    if (characterPositionWorld.x >= gameMap.getWidth() * 32 - (650 - 32) / 2) {
        characterImagePosX = (650 - (gameMap.getWidth() - x) * 32);
    }
    if (characterPositionWorld.y <= (600 - 32) / 2) {
        characterImagePosY = y * 32 - 28;
    }
    if (characterPositionWorld.y >= gameMap.getHeight() * 32 - (600 - 32) / 2) {
        characterImagePosY = (600 - (gameMap.getWidth() - y) * 32 - 28);
    }
    view.playerPartyImage->setPosition({characterImagePosX, characterImagePosY});
}

void MainView::CharacterMovingListener::onMessage(const MessageParameters &messageParameters) {
    PartyPtr partyPtr = Game::getInstance().getPlayerParty();
    int dx = messageParameters.getParameter("dx").getInt();
    int dy = messageParameters.getParameter("dy").getInt();
    int x = view.playerPartyImage->getPosition().x + dx * 32;
    int y = view.playerPartyImage->getPosition().y + dy * 32;
    AnimationPtr animationPtr{new MovementAnimation(view.playerPartyImage, {x, y}, 500)};
    view.addAnimation(animationPtr);
}
