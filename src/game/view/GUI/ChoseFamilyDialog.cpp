//
// Created by TriD on 01.06.2015.
//

#include "ChoseFamilyDialog.h"
#include "../../../view/Screen.h"
#include "../../MainState.h"
#include "FamilyButton.h"
#include "../../FamilyManager.h"
#include "../../../view/GUI/Label.h"

void ChoseFamilyDialog::setUp() {
    clearWidgets();

    addWidget(label);

    const Families &families = FamilyManager::getInstance().getFamilies();

    //Prepare dialog
    int height = families.size() * buttonHeight + 14;
    setHeight(height);
    int y = (Screen::getInstance().getHeight() - height) / 2;

    for (int i = 0; i < families.size(); i++) {
        WidgetPtr button{new FamilyButton(0, i * buttonHeight + 14, getWidth(), buttonHeight, families[i], callback)};
        addWidget(button);
    }
}

ChoseFamilyDialog::ChoseFamilyDialog(int x, int y, int w, int h, UILayout &layout, Callback callback) : Dialog(x, y, w,
                                                                                                               h,
                                                                                                               layout),
                                                                                                        callback(
                                                                                                                callback) {
    label = std::shared_ptr<Widget>{new Label(0, 0, w, 14, nullptr, "Chose family")};
}
