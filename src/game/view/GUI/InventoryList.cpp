//
// Created by TriD on 01.08.2015.
//

#include <sstream>

#include "InventoryList.h"
#include "../../Character.h"
#include "../../Game.h"
#include "../../../view/GUI/Button.h"

using MEng::View::GUI::Button;
using namespace Main;
using namespace Main::View::GUI;

void InventoryList::update() {
    Character& playerCharacter = Game::getInstance().getPlayerCharacter();
    Items items = playerCharacter.getItems();
    
    for (int i = 0; i < items.size(); i++) {
        std::stringstream ss;

        std::shared_ptr<Item> &item = items[i];
        if (item->getType() == ItemType::Armor) {
            ss << "Armor";
        }
        else {
            ss << "Weapon";
        }
        if (item->isEquiped()) {
            ss << "*";
        }

        auto callback = [this, item, &playerCharacter](){
            if (item->isEquiped()) {
                item->getType() == ItemType::Armor ? playerCharacter.unequipArmor() : playerCharacter.unequipWeapon();
                this->update();
            }
            else {
                Game::getInstance().getPlayerCharacter().equip(item);
                this->update();
            }
        };
        MEng::View::GUI::WidgetPtr button{new Button{0, i * 30, 150, 30, ss.str(), callback}};
        addWidget(button);
    }
    setHeight(items.size() * 30);
}
