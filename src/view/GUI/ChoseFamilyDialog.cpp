//
// Created by TriD on 01.06.2015.
//

#include "ChoseFamilyDialog.h"
#include "../Screen.h"
#include "../../game/MainState.h"
#include "FamilyButton.h"
#include "../../game/FamilyManager.h"

void ChoseFamilyDialog::show() {
    Widget::show();

    const Families& families = FamilyManager::getInstance().getFamilies();

    //Prepare dialog
    int height = families.size() * buttonHeight;
    setHeight(height);
    int y = (Screen::getInstance().getHeight() - height) / 2;
    clearWidgets();

    for (int i = 0; i < families.size(); i++) {
        WidgetPtr button{new FamilyButton(0, i * buttonHeight, getWidth(), buttonHeight, families[i], callback)};
        addWidget(button);
    }
}
