//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_VIEW_H
#define FAMILY_BUSINESS_VIEW_H

#include "GUI/UILayout.h"
#include "Screen.h"
#include "../Point.h"

class View {
private:
    UILayout layout;
public:
    virtual void draw(SDL_Renderer *renderer);
    virtual void onClick(const Point& point, int button);
    virtual void onKeyUp(int key) {};
    virtual void onKeyDown(int key) {};
    virtual void update(int timeDelta) {}

    UILayout& getLayout() { return layout; }
};

using ViewPtr = std::shared_ptr<View>;

#endif //FAMILY_BUSINESS_VIEW_H
