//
// Created by TriD on 27.05.2015.
//

#ifndef FAMILY_BUSINESS_MENU_H
#define FAMILY_BUSINESS_MENU_H

#include "Widget.h"
#include "UILayout.h"

#include <memory>
#include <vector>

namespace MEng {
    namespace View {
        namespace GUI {

            using Widgets = std::vector<WidgetPtr>;

            class Dialog : public Widget {
            private:
                Widgets widgets;
                SDL_Color backgroundColor{0, 0, 0, 0};
                UILayout &layout;
            protected:
                virtual void onRedraw(SDL_Renderer *renderer) override;

            public:
                Dialog(int x, int y, int w, int h, UILayout &layout) : Widget(x, y, w, h),
                                                                       layout(layout) { Widget::hide(); }

                void addWidget(WidgetPtr widget);

                void removeWidget(WidgetPtr widget);

                void clearWidgets();

                SDL_Color getBgColor() const { return backgroundColor; }

                void setBgColor(SDL_Color color) { Dialog::backgroundColor = color; }

                virtual bool onClick(Point point, int button) override;

                virtual void show() override {
                    Widget::show();
                    layout.setDialogActive(true);
                }

                virtual void hide() override {
                    Widget::hide();
                    layout.setDialogActive(false);
                }
            };

        }
    }
}
#endif //FAMILY_BUSINESS_MENU_H
