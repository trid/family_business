//
// Created by TriD on 24.05.2015.
//

#ifndef FAMILY_BUSINESS_SCREEN_H
#define FAMILY_BUSINESS_SCREEN_H


#include <SDL2/SDL.h>
#include <memory>

namespace MEng {
    namespace View {
        class View;

        using ViewPtr = std::shared_ptr<View>;

        class Screen {
        private:
            int width = 800;
            int height = 600;

            SDL_Window *window;
            SDL_Renderer *renderer;

            Screen();

        public:
            static Screen &getInstance() {
                static Screen instance;
                return instance;
            }

            void draw();

            SDL_Renderer *getRenderer() { return renderer; }

            int getWidth() { return width; }

            int getHeight() { return height; }
        };
    }
}

#endif //FAMILY_BUSINESS_SCREEN_H
