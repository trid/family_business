//
// Created by TriD on 01.06.2015.
//

#include "ChoseCharacterDialog.h"
#include "CharacterButton.h"
#include "../../../view/Screen.h"
#include "../../../view/GUI/Label.h"

void ChoseCharacterDialog::setUp(FamilyPtr familyPtr) {
    clearWidgets();

    addWidget(label);

    int i = 0;

    if (familyPtr->getFather()->isAlive()) {
        addWidget(WidgetPtr(new CharacterButton(0, 14, getWidth(), 30, familyPtr->getFather(), callback)));
        ++i;
    }
    if (familyPtr->getMother()->isAlive()) {
        addWidget(WidgetPtr(new CharacterButton(0, i * 30 + 14, getWidth(), 30, familyPtr->getMother(), callback)));
        ++i;
    }

    Children& children = familyPtr->getChildren();

    for (auto child: children) {
        if (!child->isAlive()) {
            continue;
        }
        addWidget(WidgetPtr(
                new CharacterButton(0, i * 30 + 14, getWidth(), 30, child, callback)));
        ++i;
    }

    unsigned int height = (children.size() + 2) * 30 + 14;
    setHeight(height);
    int y = (Screen::getInstance().getHeight() - height) / 2;
    setTop(y);
}

ChoseCharacterDialog::ChoseCharacterDialog(int x, int y, int w, int h, CharacterBtnCallback callback) : Dialog(x, y, w, h),
                                                                                                        callback(callback) {
    label = std::shared_ptr<Widget>{new Label(0, 0, w, 14, nullptr, "Chose character")};
}
