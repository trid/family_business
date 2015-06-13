//
// Created by dmitry-khovyakov on 5/25/15.
//

#include "MainView.h"
#include "GUI/ChoseFamilyDialog.h"
#include "GUI/ChoseCharacterDialog.h"

void MainView::draw() {
    View::draw();
}

MainView::MainView() {
    UILayout& layout = getLayout();
    familyDialogWidget = WidgetPtr{new ChoseFamilyDialog((800 - 200) / 2, (600 - 60) / 2, 200, 0,
                                                       [this](FamilyPtr familyPtr) { showFamilyDialog(familyPtr); })};
    familyDialogWidget->show();
    layout.addWidget(familyDialogWidget);
    choseCharacterDialog = ChoseCharacterDialogPtr{new ChoseCharacterDialog((800 - 200) / 2, (600 - 60) / 2, 200, 60)};
    choseCharacterDialog->hide();
    layout.addWidget(choseCharacterDialog);
}

void MainView::showFamilyDialog(FamilyPtr familyPtr) {
    familyDialogWidget->hide();
    choseCharacterDialog->setUp(familyPtr);
    choseCharacterDialog->show();
}
