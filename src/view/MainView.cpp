//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"

void MainView::draw() {

}

MainView::MainView() {
    UILayout& layout = getLayout();
    WidgetPtr  familyDialogWidget{new ChoseFamilyDialog((800 - 100) / 2, (600 - 60) / 2, 100, 60)};
    layout.addWidget(familyDialogWidget);
    WidgetPtr choseCharacterDialog{new ChoseCharacterDialog((800 - 100) / 2, (600 - 60) / 2, 100, 60)};
    choseCharacterDialog->hide();
    layout.addWidget(choseCharacterDialog);
}
