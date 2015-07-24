//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_VIEW_H
#define FAMILY_BUSINESS_VIEW_H

#include <list>

#include "GUI/UILayout.h"
#include "Screen.h"
#include "../Point.h"
#include "Drawable.h"

class View {
private:
    UILayout layout;
    std::list<DrawablePtr> drawables;
public:
    virtual void draw(SDL_Renderer *renderer);
    virtual void onClick(const Point& point, int button);
    virtual void onKeyUp(int key) {};
    virtual void onKeyDown(int key) {};
    virtual void update(int timeDelta) {}

    UILayout& getLayout() { return layout; }

    void addDrawable(DrawablePtr drawable) { drawables.push_back(drawable); }
    void removeDrawable(DrawablePtr drawablePtr) { drawables.remove(drawablePtr); }
};

using ViewPtr = std::shared_ptr<View>;

#endif //FAMILY_BUSINESS_VIEW_H
