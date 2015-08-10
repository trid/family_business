//
// Created by dmitry-khovyakov on 5/25/15.
//

#ifndef FAMILY_BUSINESS_VIEW_H
#define FAMILY_BUSINESS_VIEW_H

#include <algorithm>
#include <vector>

#include "GUI/UILayout.h"
#include "Screen.h"
#include "../Point.h"
#include "Drawable.h"
#include "Animation.h"

class View {
private:
    UILayout layout;
    std::vector<DrawablePtr> drawables;
    std::vector<AnimationPtr> animations;
public:
    virtual ~View() {}

    virtual void draw(SDL_Renderer *renderer);
    virtual void onClick(const Point& point, int button);
    virtual void onKeyUp(int key) {};
    virtual void onKeyDown(int key) {};
    virtual void update(int timeDelta);

    UILayout& getLayout() { return layout; }

    void addDrawable(DrawablePtr drawable) { drawables.push_back(drawable); }
    void removeDrawable(DrawablePtr drawablePtr) { drawables.erase(std::remove(drawables.begin(), drawables.end(), drawablePtr), drawables.end()); }

    void addAnimation(AnimationPtr animation) { animations.push_back(animation); }
};

using ViewPtr = std::shared_ptr<View>;

#endif //FAMILY_BUSINESS_VIEW_H
