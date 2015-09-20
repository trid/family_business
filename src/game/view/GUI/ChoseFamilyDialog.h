//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
#define FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H

#include "../../../view/GUI/Dialog.h"
#include "../../../view/View.h"
#include "FamilyButton.h"

namespace Main {
    namespace View {
        namespace GUI {

            class ChoseFamilyDialog : public MEng::View::GUI::Dialog {
            private:
                static constexpr int buttonHeight = 30;
                FamilyButton::Callback callback;
                MEng::View::GUI::WidgetPtr label;
            public:
                ChoseFamilyDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout,
                                  FamilyButton::Callback callback);

                void setUp();
            };

        }
    }
}

#endif //FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
