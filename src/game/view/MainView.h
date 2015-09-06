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
#include "../../view/Image.h"
#include "GUI/MonsterImage.h"
#include "../../view/GUI/Label.h"


class MainView : public MEng::View::View {
    MEng::View::GUI::WidgetPtr familyDialogWidget;
    ChoseCharacterDialogPtr choseCharacterDialog;
    HireCharacterDialogPtr hireCharacterDialog;

    MEng::View::GUI::WidgetPtr mainMenu;
    MEng::View::GUI::LabelPtr dateLabel;

    MEng::View::DrawablePtr mapView{new MapPresentation};
    std::vector<MonsterImagePtr> monsterViews;

    int dx{}, dy{};

    MEng::View::ImagePtr playerPartyImage;

    void showFamilyDialog(int familyId);
    void choseCharacter(int characterId);
    void centerOnCharacter();
    void loadMonsterViews();
    void updateMonsterViews();
    void clearMonsterViews();
    void updateDate();

    class CharacterMovedListener : public MEng::MessageListener{
    private:
        MainView& view;
    public:
        CharacterMovedListener(MainView& view): view(view) {}
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };

    class PartyMovingListener : public MEng::MessageListener{
    private:
        MainView& view;
    public:
        PartyMovingListener(MainView& view): view(view) {}
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };

    class GameLoadedListener: public MEng::MessageListener{
    private:
        MainView& view;
    public:
        GameLoadedListener(MainView &view) : view(view) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };

    class MovementRestartedListener: public MEng::MessageListener {
    private:
        MainView& view;
    public:
        MovementRestartedListener(MainView &view) : view(view) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
    };

    class NewGameListener: public MEng::MessageListener {
    private:
        MainView& view;
    public:
        NewGameListener(MainView &view) : view(view) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };

    class NewDayListener: public MEng::MessageListener {
    private:
        MainView& view;
    public:
        NewDayListener(MainView &view) : view(view) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };
public:
    MainView();

    virtual void draw(SDL_Renderer *renderer) override;
    virtual void update(int timeDelta) override;

    virtual void onKeyUp(int key) override;
    virtual void onKeyDown(int key) override;

    void showHireDialog(Building &house);
    void showFamiliesDialog();

    void addCharacterToParty(int characterId);
};


#endif //FAMILY_BUSINESS_MAINVIEW_H
