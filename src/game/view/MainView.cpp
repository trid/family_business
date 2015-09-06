//
// Created by dmitry-khovyakov on 5/25/15.
//

#include <algorithm>
#include <sstream>

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"
#include "../House.h"
#include "../Game.h"
#include "GUI/CharacterPanel.h"
#include "../../view/SpriteManager.h"
#include "../../MessageManager.h"
#include "../../view/MovementAnimation.h"
#include "GUI/GameMenu.h"
#include "../HouseManager.h"
#include "../FamilyManager.h"

using namespace MEng;
using namespace MEng::View;

void MainView::draw(SDL_Renderer *renderer) {
    View::draw(renderer);
}

MainView::MainView() {
    UILayout &layout = getLayout();
    ChoseFamilyDialog *dialog = new ChoseFamilyDialog((800 - 200) / 2, (600 - 60) / 2, 200, 0, layout,
                                                      [this](int familyId) { showFamilyDialog(familyId); });
    familyDialogWidget = WidgetPtr{dialog};

    layout.addWidget(familyDialogWidget);
    choseCharacterDialog = ChoseCharacterDialogPtr{
            new ChoseCharacterDialog((800 - 200) / 2, (600 - 60) / 2, 200, 60, layout,
                                     [this](int characterId) { choseCharacter(characterId); })};
    layout.addWidget(choseCharacterDialog);

    auto addCharacterToParty = [this](int characterId) {
        this->addCharacterToParty(characterId);
    };

    hireCharacterDialog = std::make_shared<HireCharacterDialog>((800 - 200) / 2, (600 - 60) / 2, 200, 60, layout,
                                                                addCharacterToParty);
    layout.addWidget(hireCharacterDialog);
    WidgetPtr sidePanel{new CharacterPanel(650, 0, 150, 600, nullptr)};
    layout.addWidget(sidePanel);

    mainMenu = std::make_shared<GameMenu>(0, 0, 150, 180, nullptr);
    layout.addWidget(mainMenu);
    mainMenu->hide();
    mainMenu->centrate();

    dateLabel = std::make_shared<Label>(550, 0, 50, 20, nullptr, "");
    layout.addWidget(dateLabel);

    playerPartyImage = ImagePtr{new Image(SpriteManager::getInstance().getTexture("res/images/human.png"), {800, 600})};

    updateDate();

    addDrawable(mapView);
    addDrawable(playerPartyImage);

    MessageManager &messageManager = MessageManager::getInstance();
    messageManager.addListener("character_moved", std::make_shared<CharacterMovedListener>(*this));
    messageManager.addListener("party_moving", std::make_shared<PartyMovingListener>(*this));
    messageManager.addListener("game_loaded", std::make_shared<GameLoadedListener>(*this));
    messageManager.addListener("movement_restart", std::make_shared<MovementRestartedListener>(*this));
    messageManager.addListener("new_game", std::make_shared<NewGameListener>(*this));
    messageManager.addListener("new_day", std::make_shared<NewDayListener>(*this));
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
    Party& party = game.getPlayerParty();
    gameMap.getTile(posX, posY).setParty(party.getId());
    party.setX(posX);
    party.setY(posY);
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
    updateMonsterViews();
}

void MainView::update(int timeDelta) {
    View::update(timeDelta);
}

void MainView::onKeyUp(int key) {
    View::onKeyUp(key);
    if (key == SDLK_ESCAPE) {
        if (mainMenu->isVisible()) {
            mainMenu->hide();
        }
        else {
            mainMenu->show();
        }
    }
}

void MainView::onKeyDown(int key) {
    View::onKeyDown(key);
}

void MainView::centerOnCharacter() {
    Party& party = Game::getInstance().getPlayerParty();
    if (party.getCreatures().size()) {
        GameMap &gameMap = Game::getInstance().getMap();
        dx = -party.getX() * 32 - 16 + (Screen::getInstance().getWidth() - 150) / 2;
        dy = -party.getY() * 32 - 16 + Screen::getInstance().getHeight() / 2;
        static_cast<MapPresentation *>(mapView.get())->setDeltas(dx, dy);
    }
}

void MainView::showHireDialog(House &house) {
    auto addCharacterToParty = [this, house](int character) {
        this->addCharacterToParty(character);
    };
    hireCharacterDialog->setCallback(addCharacterToParty);
    hireCharacterDialog->setUp(house);
    hireCharacterDialog->show();
}

void MainView::addCharacterToParty(int characterId) {
    if (Game::getInstance().getPlayerParty().addCreature(characterId)) {
        Character& character = static_cast<Character&>(getCreatureById(characterId));
        Family& family = getFamilyById(character.getFamilyId());
        House& house = getHouseById(family.getHome());
        std::vector<int>& characters = house.getCharacters();
        auto iter = std::remove(characters.begin(), characters.end(), characterId);
        characters.erase(iter, characters.end());
    }
    hireCharacterDialog->hide();
}

void MainView::CharacterMovedListener::onMessage(const MessageParameters &messageParameters) {
    int partyId = messageParameters.getParameter("partyId").getInt();
    if (partyId == Game::getInstance().getPlayerParty().getId()) {
        int x = messageParameters.getParameter("x").getInt();
        int y = messageParameters.getParameter("y").getInt();

        Point characterPositionWorld{x * 32, y * 32};
        int characterImagePosX = (650 - 32) / 2;
        int characterImagePosY = (600 - 32) / 2 - 28;

        GameMap &gameMap = Game::getInstance().getMap();

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
    view.updateMonsterViews();
}

void MainView::PartyMovingListener::onMessage(const MessageParameters &messageParameters) {
    Party& playerParty = Game::getInstance().getPlayerParty();
    int partyId = messageParameters.getParameter("partyId").getInt();
    int dx = messageParameters.getParameter("dx").getInt();
    int dy = messageParameters.getParameter("dy").getInt();
    ImagePtr imagePtr;
    if (partyId == playerParty.getId()) {
        imagePtr = view.playerPartyImage;
    }
    else {
        auto comp = [partyId](MonsterImagePtr m){ return m->getPartyId() == partyId; };
        auto iter = std::find_if(view.monsterViews.begin(), view.monsterViews.end(), comp);
        imagePtr = *iter;
    }
    int x = imagePtr->getPosition().x + dx * 32;
    int y = imagePtr->getPosition().y + dy * 32;
    AnimationPtr animationPtr{new MovementAnimation(imagePtr, {x, y}, 500)};
    view.addAnimation(animationPtr);
}

void MainView::showFamiliesDialog() {
    std::shared_ptr<ChoseFamilyDialog> dialog = std::static_pointer_cast<ChoseFamilyDialog>(familyDialogWidget);
    dialog->setUp();
    familyDialogWidget->show();
}

void MainView::GameLoadedListener::onMessage(const MessageParameters &messageParameters) {
    view.centerOnCharacter();

    Game &game = Game::getInstance();
    GameMap& gameMap = game.getMap();
    Party& party = game.getPlayerParty();

    Point characterPositionWorld{party.getX() * 32, party.getY() * 32};
    int characterImagePosX = (650 - 32) / 2;
    int characterImagePosY = (600 - 32) / 2 - 28;


    if (characterPositionWorld.x <= (650 - 32) / 2) {
        characterImagePosX = party.getX() * 32;
    }
    if (characterPositionWorld.x >= gameMap.getWidth() * 32 - (650 - 32) / 2) {
        characterImagePosX = (650 - (gameMap.getWidth() - party.getY()) * 32);
    }
    if (characterPositionWorld.y <= (600 - 32) / 2) {
        characterImagePosY = party.getY() * 32 - 28;
    }
    if (characterPositionWorld.y >= gameMap.getHeight() * 32 - (600 - 32) / 2) {
        characterImagePosY = (600 - (gameMap.getWidth() - party.getY()) * 32 - 28);
    }
    view.playerPartyImage->setPosition({characterImagePosX, characterImagePosY});
    view.clearMonsterViews();
    view.loadMonsterViews();
    view.updateDate();
}

void MainView::MovementRestartedListener::onMessage(const MessageParameters &messageParameters) {
    int partyId = messageParameters.getParameter("partyId").getInt();
    if (partyId == Game::getInstance().getPlayerParty().getId()) {
        auto partyLocation = view.playerPartyImage->getPosition();
        int time = messageParameters.getParameter("time").getInt();
        int dx = messageParameters.getParameter("x").getInt();
        int dy = messageParameters.getParameter("y").getInt();

        partyLocation.x = partyLocation.x + dx * time / 500;
        partyLocation.y = partyLocation.y + dy * time / 500;
        AnimationPtr animationPtr = std::make_shared<MovementAnimation>(view.playerPartyImage, Point{dx, dy},
                                                                        500 - time);
        view.addAnimation(animationPtr);
    }
}

void MainView::loadMonsterViews() {
    PartyManager &manager = PartyManager::getInstance();
    SDL_Texture *texture = SpriteManager::getInstance().getTexture("res/images/monster.png");
    for (auto& item: manager.getParties()) {
        if (item->getSide() == Side::AI) {
            monsterViews.emplace_back(new MonsterImage(texture, item->getId()));
            addDrawable(monsterViews.back());
        }
    }
}

void MainView::updateMonsterViews() {
    PartyManager &partyManager = PartyManager::getInstance();
    Party& playerParty = Game::getInstance().getPlayerParty();
    Point playerPosition = playerParty.getPosition();
    Point imagePosition = playerPartyImage->getPosition();
    for (auto item: monsterViews) {
        Party& monsterParty = partyManager.getParty(item->getPartyId());
        Point distance = monsterParty.getPosition() - playerPosition;
        item->setPosition({imagePosition.x + distance.x * 32, imagePosition.y + distance.y * 32 + 28});
    }
}

void MainView::clearMonsterViews() {
    for (auto item: monsterViews) {
        removeDrawable(item);
    }
    monsterViews.clear();
}

void MainView::NewGameListener::onMessage(const MessageParameters &messageParameters) {
    view.loadMonsterViews();
}

void MainView::updateDate() {
    int date = Game::getInstance().getDate();
    int years = date / (12 * 30);
    date = date - years * 12 * 30;
    int month = date / 30;
    int days = date - month * 30;
    std::stringstream ss;

    ss << days << "." << month << "." << years;
    dateLabel->setText(ss.str());
}

void MainView::NewDayListener::onMessage(const MessageParameters &messageParameters) {
    view.updateDate();
}
