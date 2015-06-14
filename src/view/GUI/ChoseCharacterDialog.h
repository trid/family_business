//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
#define FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H

#include "Dialog.h"
#include "../../game/Family.h"
#include "CharacterButton.h"


class ChoseCharacterDialog : public Dialog {
private:
    CharacterBtnCallback callback;
public:
    ChoseCharacterDialog(int x, int y, int w, int h, CharacterBtnCallback callback) : Dialog(x, y, w, h),
                                                                                      callback(callback) { }

    void setUp(FamilyPtr familyPtr);
};

using ChoseCharacterDialogPtr = std::shared_ptr<ChoseCharacterDialog>;

#endif //FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
