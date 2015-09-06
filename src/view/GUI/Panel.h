//
// Created by TriD on 01.08.2015.
//

#ifndef FAMILY_BUSINESS_PANEL_H
#define FAMILY_BUSINESS_PANEL_H

#include <vector>

#include "Widget.h"
#include "UILayout.h"

namespace MEng {
    namespace View {
        namespace GUI {

            using Widgets = std::vector<WidgetPtr>;

            class Panel : public Widget {
            private:
                Widgets widgets;
                SDL_Color backgroundColor{0, 0, 0, 0};
            protected:
                virtual void onRedraw(SDL_Renderer *renderer) override;

            public:
                Panel(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent) : Widget(x, y, w, h,
                                                                                                  parent) { }

                void addWidget(WidgetPtr widget);

                void removeWidget(WidgetPtr widget);

                void clearWidgets();

                SDL_Color getBgColor() const { return backgroundColor; }

                void setBgColor(SDL_Color color) { this->backgroundColor = color; }

                virtual bool onClick(Point point, int button) override;
            };

        }
    }
}

#endif //FAMILY_BUSINESS_PANEL_H
