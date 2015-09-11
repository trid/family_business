//
// Created by TriD on 01.08.2015.
//

#ifndef FAMILY_BUSINESS_INVENTORYLIST_H
#define FAMILY_BUSINESS_INVENTORYLIST_H


#include <vector>

#include "../../../view/GUI/Panel.h"

namespace Main {
    namespace View {
        namespace GUI {

            class InventoryList : public MEng::View::GUI::Panel {

            public:
                InventoryList(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent) : Panel(x, y, w, h,
                                                                                                         parent) { }

                void update();
            };

            using InventoryListPtr = std::shared_ptr<InventoryList>;

        }
    }
}

#endif //FAMILY_BUSINESS_INVENTORYLIST_H
