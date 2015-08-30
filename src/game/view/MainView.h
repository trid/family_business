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


class MainView : public View {
    WidgetPtr familyDialogWidget;
    ChoseCharacterDialogPtr choseCharacterDialog;
    HireCharacterDialogPtr hireCharacterDialog;

    WidgetPtr mainMenu;
    LabelPtr dateLabel;

    DrawablePtr mapView{new MapPresentation};
    std::vector<MonsterImagePtr> monsterViews;

    int dx{}, dy{};

    ImagePtr playerPartyImage;

    void showFamilyDialog(int familyId);
    void choseCharacter(int characterId);
    void centerOnCharacter();
    void loadMonsterViews();
    void updateMonsterViews();
    void clearMonsterViews();
    void updateDate();

    class CharacterMovedListener : public MessageListener{
    private:
        MainView& view;
    public:
        CharacterMovedListener(MainView& view): view(view) {}
        virtual void onMessage(const MessageParameters &messageParameters);
    };

    class CharacterMovingListener : public MessageListener{
    private:
        MainView& view;
    public:
        CharacterMovingListener(MainView& view): view(view) {}
        virtual void onMessage(const MessageParameters &messageParameters);
    };

    class GameLoadedListener: public MessageListener{
    private:
        MainView& view;
    public:
        GameLoadedListener(MainView &view) : view(view) { }
        virtual void onMessage(const MessageParameters &messageParameters);
    };

    class MovementRestartedListener: public MessageListener {
    private:
        MainView& view;
    public:
        MovementRestartedListener(MainView &view) : view(view) { }
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };

    class NewGameListener: public MessageListener {
    private:
        MainView& view;
    public:
        NewGameListener(MainView &view) : view(view) { }
        virtual void onMessage(const MessageParameters &messageParameters);
    };

    class NewDayListener: public MessageListener {
    private:
        MainView& view;
    public:
        NewDayListener(MainView &view) : view(view) { }
        virtual void onMessage(const MessageParameters &messageParameters);
    };
public:
    MainView();

    virtual void draw(SDL_Renderer *renderer) override;
    virtual void update(int timeDelta) override;

    virtual void onKeyUp(int key) override;
    virtual void onKeyDown(int key) override;

    void showHireDialog(House &house);
    void showFamiliesDialog();

    void addCharacterToParty(int characterId);
};


#endif //FAMILY_BUSINESS_MAINVIEW_H
