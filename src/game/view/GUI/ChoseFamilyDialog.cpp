//
// Created by TriD on 01.06.2015.
//

#include "ChoseFamilyDialog.h"
#include "../../../view/Screen.h"
#include "../../MainState.h"
#include "FamilyButton.h"
#include "../../FamilyManager.h"

void ChoseFamilyDialog::setUp() {
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
