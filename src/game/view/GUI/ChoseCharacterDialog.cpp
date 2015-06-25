//
// Created by TriD on 01.06.2015.
//

#include "ChoseCharacterDialog.h"
#include "CharacterButton.h"
#include "../../../view/Screen.h"

void ChoseCharacterDialog::setUp(FamilyPtr familyPtr) {
    clearWidgets();

    addWidget(WidgetPtr(new CharacterButton(0, 0, getWidth(), 30, familyPtr->getFather(), callback)));
    addWidget(WidgetPtr(new CharacterButton(0, 30, getWidth(), 30, familyPtr->getMother(), callback)));

    Children& children = familyPtr->getChildren();

    for (int i = 0; i < children.size(); i++) {
        addWidget(WidgetPtr(
                new CharacterButton(0, i * 30 + 60, getWidth(), 30, children[i], callback)));
    }

    unsigned int height = (children.size() + 2) * 30;
    setHeight(height);
    int y = (Screen::getInstance().getHeight() - height) / 2;
    setTop(y);
}
