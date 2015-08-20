//
// Created by TriD on 19.07.2015.
//

#ifndef FAMILY_BUSINESS_HIRECHARACTERMENU_H
#define FAMILY_BUSINESS_HIRECHARACTERMENU_H


#include "../../../view/GUI/Dialog.h"
#include "../../House.h"
#include "CharacterButton.h"

class HireCharacterDialog : public Dialog {
    CharacterBtnCallback callback;
    int houseId;
    WidgetPtr label;
public:
    HireCharacterDialog(int x, int y, int w, int h, UILayout &layout,
                                                 CharacterBtnCallback callback);

    void setUp(House &house);
    void setCallback(CharacterBtnCallback callback) { this->callback = callback; }
};

using HireCharacterDialogPtr = std::shared_ptr<HireCharacterDialog>;

#endif //FAMILY_BUSINESS_HIRECHARACTERMENU_H
