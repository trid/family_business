//
// Created by TriD on 15.06.2015.
//

#ifndef FAMILY_BUSINESS_MAPVIEW_H
#define FAMILY_BUSINESS_MAPVIEW_H


#include <SDL2/SDL.h>
#include "../../view/Drawable.h"
#include "../../MessageListener.h"
#include "../../Point.h"

namespace Main {
    namespace View {

        class MapPresentation : public MEng::View::Drawable {
        private:
            SDL_Texture *grass;
            SDL_Texture *house;
            SDL_Texture *character;
            SDL_Texture *monster;
            SDL_Texture *tree;
            SDL_Texture *road;

            int dx{}, dy{};

            class CharacterMoveListener : public MEng::MessageListener {
            private:
                MapPresentation &mapPresentation;
            public:
                CharacterMoveListener(MapPresentation &mapPresentation) : mapPresentation(mapPresentation) { }

                virtual void onMessage(const MEng::MessageParameters &messageParameters) override;
            };

        public:
            MapPresentation();

            void draw(SDL_Renderer *renderer) override;

            void update(int timeDelta);

            void setDeltas(int dx, int dy);
        };

    }
}

#endif //FAMILY_BUSINESS_MAPVIEW_H
