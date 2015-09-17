//
// Created by TriD on 21.06.2015.
//

#include "MenuState.h"
#include "view/MenuView.h"

using namespace Main;
using namespace Main::View;

MenuState::MenuState() {
    setView(std::make_shared<MenuView>());
}
