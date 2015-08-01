//
// Created by TriD on 31.07.2015.
//

#ifndef FAMILY_BUSINESS_CHARACTERPANEL_H
#define FAMILY_BUSINESS_CHARACTERPANEL_H


#include "../../../view/GUI/Widget.h"
#include "../../../view/GUI/Panel.h"
#include "InventoryList.h"

class CharacterPanel: public Panel {
private:
    WidgetPtr inventoryButton;
    InventoryListPtr inventoryList;
public:
    CharacterPanel(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent);
};


#endif //FAMILY_BUSINESS_CHARACTERPANEL_H
