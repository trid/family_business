//
// Created by TriD on 13.08.2015.
//

#include "GameMenu.h"
#include "../../../view/GUI/Button.h"
#include "../../../Application.h"
#include "../../MenuState.h"
#include "../../Game.h"

using namespace MEng;

GameMenu::GameMenu(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent) : Panel(x, y, w, h, parent) {
    ButtonPtr saveButton = std::make_shared<Button>(0, 0, 150, 30, "Save", [this](){ Game::getInstance().saveGame(); this->hide(); });
    ButtonPtr loadButton = std::make_shared<Button>(0, 30, 150, 30, "Load", [this](){ Game::getInstance().loadGame(); this->hide(); });
    ButtonPtr continueButton = std::make_shared<Button>(0, 60, 150, 30, "Continue", [this]() {this->hide();});
    auto menuButtonCallback = []() {
        Application& application = Application::getInstance();
        application.popState();
        application.pushState(std::make_shared<MenuState>());
    };
    ButtonPtr menuButton = std::make_shared<Button>(0, 120, 150, 30, "Exit to Menu", menuButtonCallback);
    ButtonPtr desktopButton = std::make_shared<Button>(0, 150, 150, 30, "Exit to Desktop", []() { Application::getInstance().finish();});
    addWidget(saveButton);
    addWidget(loadButton);
    addWidget(continueButton);
    addWidget(menuButton);
    addWidget(desktopButton);
}