//
// Created by TriD on 13.08.2015.
//

#ifndef FAMILY_BUSINESS_GAMEMENU_H
#define FAMILY_BUSINESS_GAMEMENU_H


#include "../../../view/GUI/Panel.h"

class GameMenu: public MEng::View::GUI::Panel {
public:
    GameMenu(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent);
};


#endif //FAMILY_BUSINESS_GAMEMENU_H
