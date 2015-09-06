//
// Created by TriD on 19.07.2015.
//

#include "HireCharacterDialog.h"
#include "CharacterButton.h"
#include "../../../view/GUI/Label.h"

using namespace MEng::View::GUI;

void HireCharacterDialog::setUp(Building &housePtr) {
    clearWidgets();

    addWidget(label);

    auto &characters = housePtr.getCharacters();

    int i = 0;
    for (auto characterId: characters) {
        if (getCreatureById(characterId).isAlive()) {
            WidgetPtr button{new CharacterButton(0, i * 30 + 14, getWidth(), 30, characterId, callback)};
            addWidget(button);
            i++;
        }
    }
    setHeight(i * 30 + 14);
    centrate();
}

HireCharacterDialog::HireCharacterDialog(int x, int y, int w, int h, UILayout &layout,
                                         CharacterBtnCallback callback) : Dialog(x, y, w, h, layout),
                                                                          callback(callback) {
    label = std::shared_ptr<Widget>{new Label(0, 0, w, 14, nullptr, "Chose mercenary")};
}
