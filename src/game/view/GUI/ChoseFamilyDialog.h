//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
#define FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H

#include "../../../view/GUI/Dialog.h"
#include "../../../view/View.h"
#include "FamilyButton.h"


class ChoseFamilyDialog: public Dialog {
private:
    static constexpr int buttonHeight = 30;
    Callback callback;
public:
    ChoseFamilyDialog(int x, int y, int w, int h, Callback callback) : Dialog(x, y, w, h), callback(callback) { }

    virtual void show() override;
};


#endif //FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
