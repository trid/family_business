//
// Created by TriD on 19.07.2015.
//

#include "HireCharacterDialog.h"
#include "CharacterButton.h"

void HireCharacterDialog::setUp(HousePtr housePtr) {
    clearWidgets();

    auto& characters = housePtr->getCharacters();

    int i = 0;
    for (auto character: characters) {
        if (character->isAlive()) {
            WidgetPtr button{new CharacterButton(0, i * 30, getWidth(), 30, character, callback)};
            addWidget(button);
            i++;
        }
    }
    setHeight(i * 30);
    centrate();
}
