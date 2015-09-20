//
// Created by TriD on 18.09.2015.
//

#ifndef FAMILY_BUSINESS_HOUSEDIALOG_H
#define FAMILY_BUSINESS_HOUSEDIALOG_H

#include "../../../view/GUI/Dialog.h"
#include "../../../view/GUI/Button.h"

namespace Main {
    namespace View {
        namespace GUI {

            using MEng::View::GUI::Dialog;
            using MEng::View::GUI::Callback;
            using MEng::View::GUI::ButtonPtr;

            class HouseDialog: public Dialog {
            private:
                int houseId;
                ButtonPtr hireButton;
                ButtonPtr orderButton;
            public:
                HouseDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout);
                void setUp(int houseId) { this->houseId = houseId; }
                void setCallbacks(Callback hireCallback, Callback orderCallback);

                using HouseDialogPtr = std::shared_ptr<HouseDialog>;
            };

        }
    }
}

#endif //FAMILY_BUSINESS_HOUSEDIALOG_H
