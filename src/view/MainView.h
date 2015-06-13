//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_MAPVIEW_H
#define FAMILY_BUSINESS_MAPVIEW_H


#include "View.h"
#include "../game/Family.h"
#include "GUI/ChoseCharacterDialog.h"


class MainView : public View {
    WidgetPtr familyDialogWidget;
    ChoseCharacterDialogPtr choseCharacterDialog;

    void showFamilyDialog(FamilyPtr familyPtr);
public:
    MainView();

    virtual void draw() override;
};


#endif //FAMILY_BUSINESS_MAPVIEW_H
