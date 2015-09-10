//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_MAPSTATE_H
#define FAMILY_BUSINESS_MAPSTATE_H

#include <fstream>

#include "../State.h"
#include "view/MainView.h"
#include "view/GUI/CharacterPanel.h"
#include "Movement.h"

namespace Main {
    class MainState : public MEng::State {
        unsigned int lastTime{SDL_GetTicks()};

        class CharacterWinListener : public MEng::MessageListener {
        public:
            virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
        };

        class CharacterMovedListener : public MEng::MessageListener {
        public:
            virtual void onMessage(const MEng::MessageParameters &messageParameters);
        };

    public:
        MainState();

        virtual void onClick(const Point &point, int button) override;

        virtual void onKeyDown(int keyCode) override;

        virtual void onKeyUp(int keyCode) override;

        virtual void onActivate() override;

        virtual void onPop() override;

        virtual void run() override;

        void takeMercenary();

        void battleMonsters();

        void save(std::ofstream &out);

        void load(std::ifstream &in);
    };

}

#endif //FAMILY_BUSINESS_MAPSTATE_H
