//
// Created by TriD on 22.07.2015.
//

#ifndef FAMILY_BUSINESS_DRAWABLE_H
#define FAMILY_BUSINESS_DRAWABLE_H

#include <memory>
#include <SDL2/SDL.h>

namespace MEng {
    namespace View {

        class Drawable {
        public:
            virtual void draw(SDL_Renderer *renderer) = 0;
        };

        using DrawablePtr = std::shared_ptr<Drawable>;

    }
}

#endif //FAMILY_BUSINESS_DRAWABLE_H
