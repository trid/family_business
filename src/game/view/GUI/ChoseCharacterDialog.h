//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
#define FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H

#include "../../../view/GUI/Dialog.h"
#include "../../Family.h"
#include "CharacterButton.h"


class ChoseCharacterDialog : public MEng::View::GUI::Dialog {
private:
    Main::View::GUI::CharacterBtnCallback callback;
    MEng::View::GUI::WidgetPtr label;
public:
    ChoseCharacterDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout,
                         Main::View::GUI::CharacterBtnCallback callback);

    void setUp(int familyId);
};

using ChoseCharacterDialogPtr = std::shared_ptr<ChoseCharacterDialog>;

#endif //FAMILY_BUSINESS_CHOSECHARACTERDIALOG_H
