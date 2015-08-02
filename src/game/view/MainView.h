//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_MAINVIEW_H
#define FAMILY_BUSINESS_MAINVIEW_H


#include "../../view/View.h"
#include "../Family.h"
#include "GUI/ChoseCharacterDialog.h"
#include "MapPresentation.h"
#include "GUI/HireCharacterDialog.h"


class MainView : public View {
    WidgetPtr familyDialogWidget;
    ChoseCharacterDialogPtr choseCharacterDialog;
    HireCharacterDialogPtr hireCharacterDialog;

    DrawablePtr mapView{new MapPresentation};

    void showFamilyDialog(FamilyPtr familyPtr);
    void choseCharacter(int characterId);
    void centerOnCharacter();

    int dx{}, dy{};
public:
    MainView();

    virtual void draw(SDL_Renderer *renderer) override;
    virtual void update(int timeDelta) override;

    virtual void onKeyUp(int key) override;
    virtual void onKeyDown(int key) override;

    void showHireDialog(HousePtr housePtr);

    void addCharacterToParty(int shared_ptr, HousePtr housePtr);
};


#endif //FAMILY_BUSINESS_MAINVIEW_H
