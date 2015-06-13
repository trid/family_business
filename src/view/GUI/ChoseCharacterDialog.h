//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
#define FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H

#include "Dialog.h"
#include "../../game/Family.h"


class ChoseCharacterDialog: public Dialog {
public:
    ChoseCharacterDialog(int x, int y, int w, int h) : Dialog(x, y, w, h) { }
    void setUp(FamilyPtr familyPtr);
};

using ChoseCharacterDialogPtr = std::shared_ptr<ChoseCharacterDialog>;

#endif //FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
