//
// Created by TriD on 21.06.2015.
//

#ifndef FAMILY_BUSINESS_BATTLEVIEW_H
#define FAMILY_BUSINESS_BATTLEVIEW_H

#include <queue>
#include <vector>

#include "View.h"
#include "../battle/Battle.h"
#include "Image.h"
#include "../MessageListener.h"
#include "Sprite.h"

using BattleCreaturesView = std::vector<ImagePtr>;

class BattleView: public View {
    Battle& battle;

    SDL_Texture* grass;
    SDL_Texture* character;
    SDL_Texture* monster;
    int dx, dy;

    bool showingAnimation{false};

    BattleCreaturesView battleCreaturesView;
    ImagePtr arrowImage;
    SpritePtr attackSprite;

    std::queue<std::pair<int, Point>> movements;

    void startMovementAnimation();

    class CreatureMovingListener: public MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureMovingListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MessageParameters &messageParameters);
    };

    class AnimationFinishedListener: public MessageListener {
    private:
        BattleView& battleView;
    public:
        AnimationFinishedListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };

    class CreatureShotListener: public MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureShotListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };

    class CreatureAttackListener: public MessageListener {
    private:
        BattleView& battleView;
    public:
        CreatureAttackListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };

    class SpriteAnimationFinishedListener: public MessageListener {
    private:
        BattleView& battleView;
    public:
        SpriteAnimationFinishedListener(BattleView &battleView) : battleView(battleView) { }
        virtual void onMessage(const MessageParameters &messageParameters) override;
    };
public:
    BattleView(Battle& battle);

    virtual void draw(SDL_Renderer *renderer) override;
    bool isShowingAnimation() { return showingAnimation; }
};


#endif //FAMILY_BUSINESS_BATTLEVIEW_H
