//
// Created by TriD on 01.06.2015.
//

#include "ChoseCharacterDialog.h"
#include "CharacterButton.h"
#include "../../../view/Screen.h"
#include "../../../view/GUI/Label.h"
#include "../../FamilyManager.h"

using namespace MEng::View::GUI;
using namespace Main;
using namespace Main::View::GUI;

void ChoseCharacterDialog::setUp(int familyId) {
    clearWidgets();

    addWidget(label);

    int i = 0;

    Family& family = getFamilyById(familyId);

    if (family.getFather().isAlive()) {
        addWidget(WidgetPtr(new CharacterButton(0, 14, getWidth(), 30, family.getFatherId(), callback)));
        ++i;
    }
    if (family.getMother().isAlive()) {
        addWidget(WidgetPtr(new CharacterButton(0, i * 30 + 14, getWidth(), 30, family.getMotherId(), callback)));
        ++i;
    }

    Children &children = family.getChildren();

    for (auto child: children) {
        if (!getCreatureById(child).isAlive()) {
            continue;
        }
        addWidget(WidgetPtr(
                new CharacterButton(0, i * 30 + 14, getWidth(), 30, child, callback)));
        ++i;
    }

    unsigned int height = (children.size() + 2) * 30 + 14;
    setHeight(height);
    int y = (MEng::View::Screen::getInstance().getHeight() - height) / 2;
    setTop(y);
}

ChoseCharacterDialog::ChoseCharacterDialog(int x, int y, int w, int h, UILayout &layout,
                                           CharacterBtnCallback callback) : Dialog(x, y, w, h, layout),
                                                                            callback(callback) {
    label = std::shared_ptr<Widget>{new Label(0, 0, w, 14, nullptr, "Chose character")};
}
