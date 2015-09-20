//
// Created by TriD on 20.09.2015.
//

#ifndef FAMILY_BUSINESS_ORDERDIALOG_H
#define FAMILY_BUSINESS_ORDERDIALOG_H


#include "../../../view/GUI/Dialog.h"
#include "../../../view/GUI/Button.h"

namespace Main {
    namespace View {
        namespace GUI {

            using MEng::View::GUI::ButtonPtr;

            class OrderDialog : public MEng::View::GUI::Dialog {
            private:
                ButtonPtr weaponBtn;
                ButtonPtr armorBtn;
            public:
                OrderDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout);
                using OrderDialogPtr = std::shared_ptr<OrderDialog>;
            };
        }
    }
}


#endif //FAMILY_BUSINESS_ORDERDIALOG_H
