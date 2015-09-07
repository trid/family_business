//
// Created by TriD on 21.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLEVIEW_H
#define FAMILY_BUSINESS_BATTLEVIEW_H

#include <queue>
#include <vector>

#include "../../view/View.h"
#include "../Battle.h"
#include "../../view/Image.h"
#include "../../MessageListener.h"
#include "../../view/Sprite.h"

using BattleCreaturesView = std::vector<MEng::View::ImagePtr>;

class BattleView: public MEng::View::View {
    Battle& battle;

    SDL_Texture* grass;
    SDL_Texture* character;
    SDL_Texture* monster;
    int dx, dy;

    bool showingAnimation{false};

    BattleCreaturesView battleCreaturesView;
    MEng::View::ImagePtr arrowImage;
    MEng::View::SpritePtr attackSprite;

    std::queue<std::pair<int, Point>> movements;

    void startMovementAnimation();

    class CreatureMovingListener: public MEng::MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureMovingListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters);
    };

    class AnimationFinishedListener: public MEng::MessageListener {
    private:
        BattleView& battleView;
    public:
        AnimationFinishedListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
    };

    class CreatureShotListener: public MEng::MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureShotListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
    };

    class CreatureAttackListener: public MEng::MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureAttackListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
    };

    class SpriteAnimationFinishedListener: public MEng::MessageListener {
    private:
        BattleView& battleView;
    public:
        SpriteAnimationFinishedListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
    };
public:
    BattleView(Battle& battle);

    virtual void draw(SDL_Renderer *renderer) override;
    bool isShowingAnimation() { return showingAnimation; }
};


#endif //FAMILY_BUSINESS_BATTLEVIEW_H
