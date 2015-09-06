//
// Created by TriD on 25.05.2015.
//

#ifndef FAMILY_BUSINESS_UILAYOUT_H
#define FAMILY_BUSINESS_UILAYOUT_H

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "../../Point.h"

namespace MEng {
    namespace View {
        namespace GUI {

            class Widget;

            using WidgetPtr = std::shared_ptr<Widget>;
            using Widgets = std::vector<WidgetPtr>;

            class UILayout {
            private:
                Widgets widgets;
                bool dialogActive;
            public:
                void draw(SDL_Renderer *renderer);

                void addWidget(WidgetPtr widget);

                void removeWidget(WidgetPtr widget);

                void clearWidgets();

                bool onClick(const MEng::Point &point, int button);

                bool isDialogActive() const { return dialogActive; }

                void setDialogActive(bool dialogActive) { UILayout::dialogActive = dialogActive; }
            };

        }
    }
}

#endif //FAMILY_BUSINESS_UILAYOUT_H
