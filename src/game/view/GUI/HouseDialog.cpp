//
// Created by TriD on 18.09.2015.
//

#include "HouseDialog.h"
#include "../../../view/GUI/Button.h"

using namespace MEng::View::GUI;
using namespace Main::View::GUI;

HouseDialog::HouseDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout) : Dialog(x, y, w, h,
                                                                                                 layout) {
    hireButton = std::make_shared<Button>(0, 0, w, 20, "Hire", nullptr);
    orderButton = std::make_shared<Button>(0, 20, w, 20, "Order", nullptr);

    addWidget(hireButton);
    addWidget(orderButton);
}

void HouseDialog::setCallbacks(Callback hireCallback, Callback orderCallback) {
    hireButton->setCallback(hireCallback);
    orderButton->setCallback(orderCallback);
}
