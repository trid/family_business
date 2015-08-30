//
// Created by TriD on 25.07.2015.
//

#ifndef FAMILY_BUSINESS_LABEL_H
#define FAMILY_BUSINESS_LABEL_H


#include <SDL2/SDL_ttf.h>
#include "Widget.h"

class Label : public Widget {
private:
    std::string text;
    SDL_Texture* label{nullptr};
    TTF_Font* font;
    void refreshText();
public:
    Label(int x, int y, int w, int h, const std::shared_ptr<Widget> &parent, const std::string &text);
    void setText(const std::string &text);
protected:
    virtual void onRedraw(SDL_Renderer *renderer) override;
};

using LabelPtr = std::shared_ptr<Label>;

#endif //FAMILY_BUSINESS_LABEL_H
