//
// Created by TriD on 31.07.2015.
//

#include "CharacterPanel.h"
#include "../../../view/GUI/Button.h"
#include "../../../view/View.h"
#include "../../../Application.h"


CharacterPanel::CharacterPanel(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent) : Panel(x, y, w, h,
                                                                                                          parent) {
    inventoryList = std::make_shared<InventoryList>(0, 30, 150, 0, nullptr);
    auto callback = [this] {
        this->inventoryList->isVisible() ? this->inventoryList->hide()
                                         : (this->inventoryList->update(), this->inventoryList->show());
    };
    inventoryButton = std::make_shared<Button>(0, 0, 150, 30, "Inventory", callback);
    inventoryList->hide();
    addWidget(inventoryButton);
    addWidget(inventoryList);
}
