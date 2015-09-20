//
// Created by TriD on 20.09.2015.
//

#include "OrderDialog.h"

using namespace MEng::View::GUI;
using Main::View::GUI::OrderDialog;

OrderDialog::OrderDialog(int x, int y, int w, int h, MEng::View::GUI::UILayout &layout) : Dialog(x, y, w, h,
                                                                                                 layout) {
    weaponBtn = std::make_shared<Button>(0, 0, w, 20, "Weapon", nullptr);
    armorBtn = std::make_shared<Button>(0, 20, w, 20, "Armor", nullptr);
    addWidget(weaponBtn);
    addWidget(armorBtn);
}