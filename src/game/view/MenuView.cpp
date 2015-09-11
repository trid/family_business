//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "MenuView.h"
#include "../../view/GUI/Button.h"
#include "../../Application.h"
#include "../MainState.h"
#include "../Game.h"

using namespace MEng;
using MEng::View::GUI::Button;
using MEng::View::GUI::ButtonPtr;
using namespace Main;
using namespace Main::View;

MenuView::MenuView() {
    auto newGameCallback = [](){
        Application &application = Application::getInstance();
        application.popState();
        application.pushState(std::make_shared<MainState>());
        Game::getInstance().newGame();
    };

    auto loadGameCallback = [](){
        Application &application = Application::getInstance();
        application.popState();
        application.pushState(std::make_shared<MainState>());
        Game::getInstance().loadGame();
    };

    ButtonPtr newGameBtn = std::make_shared<Button>(0, 100, 150, 40, "New Game", newGameCallback);
    newGameBtn->centrateHorizontal();
    ButtonPtr loadGameBtn = std::make_shared<Button>(0, 180, 150, 40, "Load", loadGameCallback);
    loadGameBtn->centrateHorizontal();
    ButtonPtr exitBtn = std::make_shared<Button>(0, 260, 150, 40, "Exit", [](){ Application::getInstance().finish(); });
    exitBtn->centrateHorizontal();
    MEng::View::GUI::UILayout& layout = getLayout();
    layout.addWidget(newGameBtn);
    layout.addWidget(loadGameBtn);
    layout.addWidget(exitBtn);
}
