//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "MenuView.h"
#include "../../view/GUI/Button.h"
#include "../../Application.h"
#include "../MainState.h"
#include "../Game.h"

MenuView::MenuView() {
    auto newGameCallback = [](){
        Application &application = Application::getInstance();
        Game::getInstance().newGame();
        application.popState();
        application.pushState(std::make_shared<MainState>());
    };

    ButtonPtr newGameBtn = std::make_shared<Button>(0, 100, 150, 40, "New Game", newGameCallback);
    newGameBtn->centrateHorizontal();
    ButtonPtr loadGameBtn = std::make_shared<Button>(0, 180, 150, 40, "Load", [](){});
    loadGameBtn->centrateHorizontal();
    ButtonPtr exitBtn = std::make_shared<Button>(0, 260, 150, 40, "Exit", [](){ Application::getInstance().finish(); });
    exitBtn->centrateHorizontal();
    UILayout& layout = getLayout();
    layout.addWidget(newGameBtn);
    layout.addWidget(loadGameBtn);
    layout.addWidget(exitBtn);
}
